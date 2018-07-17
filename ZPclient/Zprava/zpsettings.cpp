#include "zpsettings.h"

ZpSettings::ZpSettings(QWidget *parent) : QWidget(parent)
{
    //getting style sheets
    File.setFileName(":/ZpSettings_stylesheet.qss");
    qDebug() << "is qt ZpSettings_stylesheet opend:" <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();

    //widget
    //top icon
    photo_label = new QLabel();
    photo_label->setObjectName("photo_label");
    photo_map = new QPixmap(":/login.png");
    photo_label->setPixmap(*photo_map);
    photo_label->setMaximumSize(100, 100);
    photo_lay = new QHBoxLayout();
    photo_lay->addWidget(photo_label);
    photo_lay->setAlignment(photo_label, Qt::AlignCenter);
    photo_widg = new QWidget();
    photo_widg->setLayout(photo_lay);

    //topic name
    topic_label = new QLabel();
    topic_label->setText("SETTINGS");
    topic_label->setObjectName("topic");
    topic_lay = new QHBoxLayout();
    topic_lay->addWidget(topic_label);
    topic_lay->setAlignment(topic_label, Qt::AlignCenter);
    topic_widg = new QWidget();
    topic_widg->setLayout(topic_lay);

    //username label
    username_topic_label = new QLabel();
    username_topic_label->setContentsMargins(5, 5, 5, 5);
    username_topic_label->setAlignment(Qt::AlignCenter);
    username_topic_label->setText("UserName");
    username_topic_label->setObjectName("topic_label");
    username_info_label = new QLabel();
    username_info_label->setContentsMargins(5, 5, 5, 5);
    username_info_label->setAlignment(Qt::AlignCenter);
    username_info_label->setText(WHOAMI->username);
    username_info_label->setObjectName("info_label");
    username_lay = new QGridLayout();
    username_lay->addWidget(username_topic_label, 0, 0, 1, 1);
    username_lay->addWidget(username_info_label, 0, 1, 1, 3);
    username_widg = new QWidget();
    username_widg->setObjectName("username_widg");
    username_widg->setLayout(username_lay);

    //email label
    email_topic_label = new QLabel();
    email_topic_label->setContentsMargins(5, 5, 5, 5);
    email_topic_label->setAlignment(Qt::AlignCenter);
    email_topic_label->setText("UserEmail");
    email_topic_label->setObjectName("topic_label");
    email_info_label = new QLabel();
    email_info_label->setContentsMargins(5, 5, 5, 5);
    email_info_label->setAlignment(Qt::AlignCenter);
    email_info_label->setText(WHOAMI->email);
    email_info_label->setObjectName("info_label");
    email_lay = new QGridLayout();
    email_lay->addWidget(email_topic_label, 0, 0, 1, 1);
    email_lay->addWidget(email_info_label, 0, 1, 1, 3);
    email_widg = new QWidget();
    email_widg->setObjectName("email_widg");
    email_widg->setLayout(email_lay);

    //whole info
    info_lay = new QVBoxLayout(this);
    info_lay->setSpacing(0);
    info_lay->setContentsMargins(0, 0, 0, 0);
    info_lay->addWidget(username_widg);
    info_lay->addWidget(email_widg);
    info_widg = new QWidget();
    info_widg->setObjectName("info_widg");
    info_widg->setLayout(info_lay);

    //buttons
    change_username_button = new QPushButton(this);
    change_username_button->setObjectName("change_button");
    change_username_button->setText("Change Username");
    change_password_button = new QPushButton(this);
    change_password_button->setObjectName("change_button");
    change_password_button->setText("Change Password");
    logout_button = new QPushButton(this);
    logout_button->setObjectName("logout_button");
    logout_button->setText("Logout");

    buttons_lay = new QGridLayout();
    buttons_lay->addWidget(change_username_button, 0, 0, 1, 4);
    buttons_lay->addWidget(change_password_button, 0, 4, 1, 4);
    buttons_lay->addWidget(logout_button, 0, 8, 1, 2);
    buttons_widg = new QWidget(this);
    buttons_widg->setLayout(buttons_lay);

    //final form
    form_lay = new QVBoxLayout();
    form_lay->addWidget(photo_widg);
    form_lay->addWidget(topic_widg);
    form_lay->addWidget(info_widg);
    form_lay->addWidget(buttons_widg);
    form_widg = new QWidget();
    form_widg->setObjectName("form_widg");
    form_widg->setLayout(form_lay);
    lay = new QHBoxLayout();
    lay->addWidget(form_widg);
    this->setLayout(lay);

    //change username
    connect(change_username_button, SIGNAL(clicked(bool)), this, SLOT(handle_change_username_button(bool)));
    change_username_widg = new QWidget();
    change_username_widg->setObjectName("change_widg");
    username_title = new QLabel(change_username_widg);
    username_title->setObjectName("change_label");
    username_title->setContentsMargins(10, 0, 10, 0);
    username_title->setText("New Username");
    username_editor = new QLineEdit(change_username_widg);
    username_editor->setObjectName("change_editor");
    username_info_lay = new QGridLayout(change_username_widg);
    username_info_lay->addWidget(username_title, 0, 0, 1, 2);
    username_info_lay->addWidget(username_editor, 0, 2, 1, 4);
    username_info_widg = new QWidget(change_username_widg);
    username_info_widg->setObjectName("change_info_widg");
    username_info_widg->setLayout(username_info_lay);
    username_submit = new QPushButton(change_username_widg);
    username_submit->setObjectName("change_submit");
    username_submit->setText("Submit");
    change_username_lay = new QVBoxLayout(change_username_widg);
    change_username_lay->addWidget(username_info_widg);
    change_username_lay->addWidget(username_submit);
    change_username_widg->setLayout(change_username_lay);
    connect(username_submit, SIGNAL(clicked(bool)), this, SLOT(handle_send_username(bool)));
    wrong_username_input_action = nullptr;

    //change password
    connect(change_password_button, SIGNAL(clicked(bool)), this, SLOT(handle_change_password_button(bool)));
    old_password_title = new QLabel();
    old_password_title->setObjectName("change_label");
    old_password_title->setContentsMargins(10, 0, 10, 0);
    old_password_title->setText("Password");
    old_password_editor = new QLineEdit();
    old_password_editor->setObjectName("change_editor");
    new_password_title = new QLabel();
    new_password_title->setObjectName("change_label");
    new_password_title->setContentsMargins(10, 0, 10, 0);
    new_password_title->setText("New Password");
    new_password_editor = new QLineEdit();
    new_password_editor->setObjectName("change_editor");
    old_password_info_lay = new QGridLayout();
    old_password_info_lay->addWidget(old_password_title, 0, 0, 1, 2);
    old_password_info_lay->addWidget(old_password_editor, 0, 2, 1, 4);
    new_password_info_lay = new QGridLayout();
    new_password_info_lay->addWidget(new_password_title, 0, 0, 1, 2);
    new_password_info_lay->addWidget(new_password_editor, 0, 2, 1, 4);
    old_password_info_widg = new QWidget();
    old_password_info_widg->setLayout(old_password_info_lay);
    new_password_info_widg = new QWidget();
    new_password_info_widg->setLayout(new_password_info_lay);
    password_info_lay = new QVBoxLayout();
    password_info_lay->addWidget(old_password_info_widg);
    password_info_lay->addWidget(new_password_info_widg);
    password_info_widg = new QWidget();
    password_info_widg->setObjectName("change_info_widg");
    password_info_widg->setLayout(password_info_lay);
    password_submit = new QPushButton();
    password_submit->setObjectName("change_submit");
    password_submit->setText("Submit");
    change_password_lay = new QVBoxLayout();
    change_password_lay->addWidget(password_info_widg);
    change_password_lay->addWidget(password_submit);
    change_password_widg = new QWidget();
    change_password_widg->setObjectName("change_widg");
    change_password_widg->setLayout(change_password_lay);
    connect(password_submit, SIGNAL(clicked(bool)), this, SLOT(handle_send_password(bool)));
    wrong_old_password_input_action = nullptr;
    wrong_new_password_input_action = nullptr;


}

void ZpSettings::resizeEvent(QResizeEvent *)
{
    change_username_widg->setFixedSize(this->width()*2/3, this->height()*2/3);
    QRect r1 = change_username_widg->geometry();
    r1.moveCenter(this->geometry().center());
    change_username_widg->setGeometry(r1);

    change_password_widg->setFixedSize(this->width()*2/3, this->height()*2/3);
    QRect r2 = change_password_widg->geometry();
    r2.moveCenter(this->geometry().center());
    change_password_widg->setGeometry(r2);
}

void ZpSettings::handle_reply(QString _reply)
{
    switch (state)
    {
        case ZpSettings::STATE::NONE:

            break;
        case ZpSettings::STATE::USERNAME:
        {
            if(_reply == "UsernameTaken")
            {
                if(wrong_username_input_action != nullptr)
                    username_editor->removeAction(wrong_username_input_action);
                wrong_username_input_action = username_editor->addAction(QIcon(":/Exclamation_sign.png"), QLineEdit::TrailingPosition);
                return;
            }
            else
            {
                change_username_widg->hide();
                change_password_widg->hide();
                username_editor->setText("");
                WHOAMI = new ZpUser(_reply);
            }
        }
        case ZpSettings::STATE::PASSWORD:
        {
            if(_reply == "IncorrectPassword")
            {
                if(wrong_old_password_input_action != nullptr)
                    old_password_editor->removeAction(wrong_old_password_input_action);
                wrong_old_password_input_action = old_password_editor->addAction(QIcon(":/Exclamation_sign.png"), QLineEdit::TrailingPosition);
                return;
            }
            else
            {
                change_username_widg->hide();
                change_password_widg->hide();
                old_password_editor->setText("");
                new_password_editor->setText("");
            }
        }
    }
}

void ZpSettings::handle_change_username_button(bool)
{
    state = ZpSettings::STATE::USERNAME;
    change_username_widg->setParent(this);
    change_password_widg->hide();
    change_username_widg->show();
}

void ZpSettings::handle_change_password_button(bool)
{
    state = ZpSettings::STATE::PASSWORD;
    change_password_widg->setParent(this);
    change_username_widg->hide();
    change_password_widg->show();
}

void ZpSettings::handle_send_username(bool)
{
    if(wrong_username_input_action != nullptr)
        username_editor->removeAction(wrong_username_input_action);
    QString new_username = username_editor->text();
    if(new_username == "")
    {
        wrong_username_input_action = username_editor->addAction(QIcon(":/Red_X.png"), QLineEdit::TrailingPosition);
        return;
    }
    network = new QNetworkAccessManager();
    request = new QNetworkRequest();
    request->setUrl(QUrl(QString::fromStdString(IP_ADDRESS) + "signup/changeusername/?old_username="+WHOAMI->username+"&new_username="+new_username));
    reply = network->get(*request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));
}

void ZpSettings::handle_send_password(bool)
{
    if(wrong_old_password_input_action != nullptr)
        old_password_editor->removeAction(wrong_old_password_input_action);
    if(wrong_new_password_input_action != nullptr)
        new_password_editor->removeAction(wrong_new_password_input_action);
    QString old_password = old_password_editor->text();
    QString new_password = new_password_editor->text();
    if(old_password == "")
    {
        wrong_old_password_input_action = old_password_editor->addAction(QIcon(":/Red_X.png"), QLineEdit::TrailingPosition);
        return;
    }
    if(new_password == "")
    {
        wrong_new_password_input_action = new_password_editor->addAction(QIcon(":/Red_X.png"), QLineEdit::TrailingPosition);
        return;
    }
    network = new QNetworkAccessManager();
    request = new QNetworkRequest();
    request->setUrl(QUrl(QString::fromStdString(IP_ADDRESS) + "signup/changepassword/?username="+WHOAMI->username+"&new_password="+new_password+"&old_password="+old_password));
    reply = network->get(*request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));
}

void ZpSettings::slotReadyRead()
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
            //qDebug() <<"-> read ok";//TODO: in QLabel
        }

        allbuf += & buf[0];
    }

    reply_string = allbuf;
    //qDebug() <<reply_string;//TODO remove this
    handle_reply(reply_string);
}

void ZpSettings::slotError(QNetworkReply::NetworkError err)
{
    //TODO: in QLabel
    qDebug() << "network error" << err;
}

void ZpSettings::slotSslErrors(QList<QSslError> err)
{
    //TODO: in QLabel
    qDebug() << "unknown network error";
}
