#include "zptextmessage.h"

ZpTextMessage::ZpTextMessage(ZpUser* _opponent, bool _amIpublisher, int _pk)
    : ZpMessage(_opponent, _amIpublisher, _pk)
{
    type = ZpMessage::Type::TEXT;
    //network
    network = new QNetworkAccessManager();
    request = new QNetworkRequest();
    request->setUrl(QUrl(QString::fromStdString(IP_ADDRESS) + "chat/getmessage/?firstside="+opponent->username+"&secondside="+WHOAMI->username+"&pk="+QString::number(pk)));
    reply = network->get(*request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));

    //getting style sheets
    File.setFileName(":/ZpTextMessage_stylesheet.qss");
    qDebug() << "is qt ZpTextMessage_stylesheet opend: " << File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();

    forward = new QLabel(this);
    forward->setObjectName("forward");
    forward->setText("forward");
    forward->setAlignment(Qt::AlignLeft);
    forward->setContentsMargins(10, 5, 10, 5);
    text_label = new QLabel(this);
    text_label->setObjectName("text_label");
    int num_lines{}, max_lenght{};
    text_label->setText(text_process(max_lenght, num_lines));
    text_label->setAlignment(Qt::AlignLeft);
    text_label->setContentsMargins(10, 5, 0, 5);
    widget_height = num_lines* 15 + 45;
    widget_width = max_lenght*8 + 90;
    datetime_label = new QLabel(this);
    datetime_label->setObjectName("datetime_label");
    datetime_label->setText(datetime.toString("hh:mm"));
    datetime_label->setAlignment(Qt::AlignBottom);
    datetime_label->setContentsMargins(10, 5, 10, 5);

    datetime_label->setProperty("amIpublisher", amIpublisher);
    datetime_label->style()->unpolish(datetime_label);
    datetime_label->style()->polish(datetime_label);
    datetime_label->update();
    text_label->setProperty("amIpublisher", amIpublisher);
    text_label->style()->unpolish(text_label);
    text_label->style()->polish(text_label);
    text_label->update();

    grid = new QGridLayout(this);
    grid->addWidget(text_label, 0, 0, 1, 10);
    grid->addWidget(datetime_label, 0, 10, 1, 1);
    grid->setSpacing(0);
    grid->setContentsMargins(0, 0, 0, 0);
    this->setLayout(grid);
    this->setFixedSize(widget_width, widget_height);
}

void ZpTextMessage::handle_reply(QString _reply)
{
    if(_reply == "InvalidChat")
    {
        qWarning() << "ZpTextMessage -> invalid chat";
        return;
    }
    //else
    QJsonDocument document = QJsonDocument::fromJson(_reply.toUtf8());
    QJsonObject object = document.object();
    is_seen = object["is_seen"].toBool();
    text = object["text"].toString();
    is_forward = object["is_forward"].toBool();
    if(is_forward)
    {
        origin_publisher = new ZpUser(object["origin_publisher"].toString());
        forward->setText("forward from "+origin_publisher->username);
        datetime_label->setProperty("amIpublisherIsforward", amIpublisher);
        datetime_label->style()->unpolish(datetime_label);
        datetime_label->style()->polish(datetime_label);
        datetime_label->update();
        text_label->setProperty("amIpublisherIsforward", amIpublisher);
        text_label->style()->unpolish(text_label);
        text_label->style()->polish(text_label);
        text_label->update();
        forward->setProperty("amIpublisherIsforward", amIpublisher);
        forward->style()->unpolish(forward);
        forward->style()->polish(forward);
        forward->update();
        grid->removeWidget(text_label);
        grid->removeWidget(datetime_label);
        grid->addWidget(forward, 0, 0, 1, 11);
        grid->addWidget(text_label, 1, 0, 4, 10);
        grid->addWidget(datetime_label, 1, 10, 4, 1);
    }
    else
    {
        origin_publisher = nullptr;
    }
    int num_lines{}, max_lenght{};
    text_label->setText(text_process(max_lenght, num_lines));
    widget_height = num_lines* 15 + 15;
    if(is_forward)  widget_height += 30;
    widget_width = max_lenght*8 + 90;
    this->setFixedSize(widget_width, widget_height);
    QDateTime tmp =  QDateTime::fromString(object["datetime"].toString(), Qt::ISODate);
    tmp = tmp.addSecs(TIMESPEC);
    if(!tmp.isValid())
    {
        datetime = QDateTime::currentDateTime();
        qWarning() << "ZpTextMessage -> invalid datetime";
        return;
    }
    datetime = tmp;
    datetime_label->setText(datetime.toString("hh:mm"));
    emit updated();
}

void ZpTextMessage::slot_menu_triggered(QAction * menu_action)
{
    if(menu_action->text() == "forward")
    {
        if(amIpublisher)
            emit message_menu_trig("forward", WHOAMI->username, this->text);
        else
            emit message_menu_trig("forward", opponent->username, this->text);
    }
}

void ZpTextMessage::updating()
{
    //network
    network = new QNetworkAccessManager();
    request = new QNetworkRequest();
    request->setUrl(QUrl(QString::fromStdString(IP_ADDRESS) + "chat/getmessage/?firstside="+opponent->username+"&secondside="+WHOAMI->username+"&pk="+QString::number(pk)));
    reply = network->get(*request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));
}

QString ZpTextMessage::text_process(int &max_lenght, int &num_lines)
{
        std::vector<QString> v;
        QStringList list = text.split('\n');
        for(auto& l : list)
            v.push_back(l);
        for(int i{}; i < v.size(); i++)
        {
            auto temp {v[i].begin()};
            auto max {v[i].begin()};
            int n {v[i].size() / 55};
            if(n > 0)
            {
                while((temp - v[i].begin()) < 55)
                {
                    max = temp;
                    temp = std::find(temp + 1, v[i].end(), ' ');
                }
                if(max - v[i].begin() == 0)
                {

                    QString tmp{};
                    for(int j{}; j < 55; j++)
                        tmp.push_back(v[i][j]);
                    QString _tmp{};
                    for(int j{55}; j < v[i].size(); j++)
                        _tmp.push_back(v[i][j]);
                    v[i] = _tmp;
                    v.insert(v.begin() + i, tmp);
                }
                else
                {
                    QString tmp{};
                    for(int j{}; j < max - v[i].begin(); j++)
                        tmp.push_back(v[i][j]);
                    QString _tmp{};
                    for(int j{static_cast<int>(max - v[i].begin() + 1)}; j < v[i].size(); j++)
                        _tmp.push_back(v[i][j]);
                    v[i] = _tmp;
                    v.insert(v.begin() + i, tmp);
                }
             }
        }
        //for(auto _v : v)
            //qDebug() << _v;

        max_lenght = v[0].size();
        num_lines = v.size();
        for(int i{}; i < v.size(); i++)
        {
            if(max_lenght < v[i].size())
                max_lenght = v[i].size();
        }
        if(is_forward)
        {
            QString forward_len{"forward from "+origin_publisher->username};
            if(forward_len.size() > max_lenght)
                max_lenght = forward_len.size();
        }
        QStringList final_list{};
        for(auto& _v : v)
            final_list << _v;
        QString final {final_list.join('\n')};

        return final;
}
