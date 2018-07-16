#include "zpsetting.h"


ZpSetting::ZpSetting(ZpUser* _user ,QWidget *parent) : QWidget(parent)
{
    apply_stylesheet();
    user = _user;
    whole_lay = new QVBoxLayout();
    setting_lay = new QHBoxLayout();
    username_lay = new QHBoxLayout();
    password_lay = new QHBoxLayout();
    timezone_lay = new QHBoxLayout();
    pic_lay = new QHBoxLayout();
    buts_lay = new QHBoxLayout();
    setting_label = new QLabel();
    username_label = new QLabel();
    timezone_label = new QLabel();
    password_label = new QLabel();
    pic_label = new QLabel();
    save_but = new QPushButton();
    logout_but = new QPushButton();
    username_change = new QLineEdit();
    password_change = new QLineEdit();
    timezone = new QComboBox();
    setting_widg = new QWidget();
    pic_widg = new QWidget();
    username_widg = new QWidget();
    password_widg = new QWidget();
    timezone_widg = new QWidget();
    buts_widg = new QWidget();

    QImage img(":/login.png");
    QImage img2 = img.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pic_label->setPixmap(QPixmap::fromImage(img2));

    setting_label->setObjectName("setting_label");
    username_label->setObjectName("username_label");
    password_label->setObjectName("password_label");
    pic_label->setObjectName("pic_label");
    save_but->setObjectName("save_but");
    logout_but->setObjectName("logout_but");
    username_change->setObjectName("username_change");
    password_change->setObjectName("password_change");
    timezone->setObjectName("timeozne");
    timezone_label->setObjectName("timezone_label");

    setting_label->setText("Zprava Setting");
    username_label->setText("Username");
    password_label->setText("Password");
    save_but->setText("Save");
    logout_but->setText("Logout");
    timezone_label->setText("TimeZone");

    timezone->addItem("GMT -12:00");
    timezone->addItem("GMT -10:00");
    timezone->addItem("GMT -8:00");
    timezone->addItem("GMT -6:00");
    timezone->addItem("GMT -4:00");
    timezone->addItem("GMT -2:00");
    timezone->addItem("GMT 0:00");
    timezone->addItem("GMT 2:00");
    timezone->addItem("GMT 4:00");
    timezone->addItem("GMT 6:00");
    timezone->addItem("GMT 8:00");
    timezone->addItem("GMT 10:00");
    timezone->addItem("GMT 12:00");

    setting_lay->addWidget(setting_label);
    setting_lay->setAlignment(setting_label,Qt::AlignCenter);
    pic_lay->addWidget(pic_label);
    pic_lay->addWidget(logout_but);
    username_lay->addWidget(username_label);
    username_lay->setSpacing(50);
    username_lay->addWidget(username_change);
    password_lay->addWidget(password_label);
    password_lay->setSpacing(50);
    password_lay->addWidget(password_change);
    timezone_lay->addWidget(timezone_label);
    timezone_lay->addWidget(timezone);
    buts_lay->addWidget(save_but);

    setting_widg->setLayout(setting_lay);
    pic_widg->setLayout(pic_lay);
    username_widg->setLayout(username_lay);
    password_widg->setLayout(password_lay);
    timezone_widg->setLayout(timezone_lay);
    buts_widg->setLayout(buts_lay);

    whole_lay->addWidget(setting_widg);
    whole_lay->addWidget(pic_widg);
    whole_lay->addWidget(username_widg);
    whole_lay->addWidget(password_widg);
    whole_lay->addWidget(timezone_widg);
    whole_lay->addWidget(buts_widg);

    empty_username_field = nullptr;
    username_exist = nullptr;

    username_change->setText(user->username);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(QPixmap(":/setting.png")));
    this->setPalette(palette);

    this->setLayout(whole_lay);

    connect(save_but,SIGNAL(clicked(bool)),this,SLOT(send_info(bool)));
    connect(logout_but,SIGNAL(clicked(bool)),this,SLOT(logout(bool)));
    connect(this,SIGNAL(signal_combobox(QString)),this,SLOT(handle_timezone(QString)));





}

void ZpSetting::apply_stylesheet()
{
    //getting style sheets
    File.setFileName(":/zpsetting_stylesheet.qss");
    qDebug() << "is qt setting_stylesheet opend:" <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();

}

void ZpSetting::initiate_networking(QList<QString>* list)
{
    network = new QNetworkAccessManager();
    request = new QNetworkRequest();
    nusername = list[0][0];
    npassword = list[0][1];
    username = list[0][2];
    request->setUrl(QUrl(QString::fromStdString(IP_ADDRESS)+"signup/setting/?nusername="+nusername+"&npassword="+npassword+"&username="+username));
    reply = network->get(*request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));
}

void ZpSetting::send_info(bool b)
{
    if(empty_username_field != nullptr)
    {
        username_change->removeAction(empty_username_field);
    }
    if(username_exist != nullptr)
    {
        username_change->removeAction(username_exist);
    }
    emit signal_combobox(timezone->currentText());
    request_list = new QList<QString>();
    request_list->append(username_change->text());
    request_list->append(password_change->text());
    request_list->append(user->username);
    initiate_networking(request_list);

}
void ZpSetting::handle_reply(QString _reply)//TODO for just returning states
{
    if(_reply == "NoChange")
    {
        qDebug()<<_reply;
    }
    else if (_reply == "Pass")
    {
        qDebug()<<"Pass Changed";
    }
    else if(_reply == "Empty")
    {
        empty_username_field = username_change->addAction(QIcon(":/Red_X.png"), QLineEdit::TrailingPosition);
    }
    else if(_reply == "Taken")
    {
        username_exist = username_change->addAction(QIcon(":/Exclamation_sign.png"), QLineEdit::TrailingPosition);
    }
    else if(_reply == "User")
    {
        qDebug()<<"Username Changed";
        delete user;
        user = new ZpUser(nusername);
        user->username = nusername;
    }
    else if(_reply == "PassUser")
    {
        delete user;
        user = new ZpUser(nusername);
        user->username = nusername;
        qDebug()<<"Usename and Password Changed";
    }
}

void ZpSetting::slotReadyRead()
{
    QString reply_string;
    std::vector<char> buf;
    qint64 chunk;

    QString allbuf;

    while(reply->bytesAvailable() > 0) {
        chunk = reply->bytesAvailable();
        if(chunk > 4096)
            chunk = 4096;

        buf.resize(chunk + 1);
        memset(& buf[0], 0, chunk + 1);

        if(chunk != reply->read(& buf[0], chunk))
        {
            qDebug() <<"-> read error";//TODO: in QLabel
        }
        else
        {
            qDebug() <<"-> read ok";//TODO: in QLabel
        }

        allbuf += & buf[0];
    }

    reply_string = allbuf;
    //qDebug() <<reply_string;//TODO remove this
    handle_reply(reply_string);
}

void ZpSetting::slotError(QNetworkReply::NetworkError err)
{
    //TODO: in QLabel
    qDebug() << "network error" << err;
}

void ZpSetting::slotSslErrors(QList<QSslError> err)
{
    //TODO: in QLabel
    qDebug() << "unknown network error";

}

void ZpSetting::logout(bool b)
{
    login_data = new QFile();
    qDebug()<<"Logut Clicked";
    login_data->setFileName(qApp->applicationDirPath() + "/login_data.txt");
    login_data->remove();
}

void ZpSetting::handle_timezone(QString s)
{
    qDebug()<<"Combobox item:"+s;
}



