#include "zpuserinfo.h"

ZpUserInfo::ZpUserInfo(QString username, QWidget *parent) : QWidget(parent)
{
    user = new ZpUser(username);
    connect(user, SIGNAL(updated()), this, SLOT(handle_update()));

    //getting style sheets
    File.setFileName(":/ZpUserInfo_stylesheet.qss");
    qDebug() << "is qt ZpUserInfo_stylesheet opend:" <<File.open(QFile::ReadOnly);
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
    topic_label->setText("USER INFO");
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
    username_info_label->setText("UnKnown!");
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
    email_info_label->setText("UnKnown!");
    email_info_label->setObjectName("info_label");
    email_lay = new QGridLayout();
    email_lay->addWidget(email_topic_label, 0, 0, 1, 1);
    email_lay->addWidget(email_info_label, 0, 1, 1, 3);
    email_widg = new QWidget();
    email_widg->setObjectName("email_widg");
    email_widg->setLayout(email_lay);

    //datetime label
    datetime_topic_label = new QLabel();
    datetime_topic_label->setContentsMargins(5, 5, 5, 5);
    datetime_topic_label->setAlignment(Qt::AlignCenter);
    datetime_topic_label->setText("Last Activity");
    datetime_topic_label->setObjectName("topic_label");
    datetime_info_label = new QLabel();
    datetime_info_label->setContentsMargins(5, 5, 5, 5);
    datetime_info_label->setAlignment(Qt::AlignCenter);
    datetime_info_label->setText("UnKnown!");
    datetime_info_label->setObjectName("info_label");
    datetime_lay = new QGridLayout();
    datetime_lay->addWidget(datetime_topic_label, 0, 0, 1, 1);
    datetime_lay->addWidget(datetime_info_label, 0, 1, 1, 3);
    datetime_widg = new QWidget();
    datetime_widg->setObjectName("datetime_widg");
    datetime_widg->setLayout(datetime_lay);

    //whole info
    info_lay = new QVBoxLayout(this);
    info_lay->setSpacing(0);
    info_lay->setContentsMargins(0, 0, 0, 0);
    info_lay->addWidget(username_widg);
    info_lay->addWidget(email_widg);
    info_lay->addWidget(datetime_widg);
    info_widg = new QWidget();
    info_widg->setObjectName("info_widg");
    info_widg->setLayout(info_lay);

    //button
    start_messaging_button = new QPushButton();
    start_messaging_button->setObjectName("start_messaging_button");
    start_messaging_button->setText("Send Message");
    start_messaging_lay = new QHBoxLayout();
    start_messaging_lay->addWidget(start_messaging_button);
    start_messaging_lay->setAlignment(start_messaging_button, Qt::AlignCenter);
    start_messaging_widg = new QWidget();
    start_messaging_widg->setLayout(start_messaging_lay);

    //final form
    form_lay = new QVBoxLayout();
    form_lay->addWidget(photo_widg);
    form_lay->addWidget(topic_widg);
    form_lay->addWidget(info_widg);
    form_lay->addWidget(start_messaging_widg);
    form_widg = new QWidget();
    form_widg->setObjectName("form_widg");
    form_widg->setLayout(form_lay);
    lay = new QHBoxLayout();
    lay->addWidget(form_widg);
    this->setLayout(lay);

}

void ZpUserInfo::handle_update()
{
    username_info_label->setText(user->username);
    email_info_label->setText(user->email);
    datetime_info_label->setText(user->last_message_datetime.toString("hh:mm"));
    if(user->username == "Invalid Username")
        datetime_info_label->setText("--:--");
    if(user->username == "Invalid Username")
    {
        start_messaging_button->setDisabled(true);
        start_messaging_button->setText("Can't Send Message");
        username_info_label->setProperty("invalid", true);
        username_info_label->style()->unpolish(username_info_label);
        username_info_label->style()->polish(username_info_label);
        username_info_label->update();
        email_info_label->setProperty("invalid", true);
        email_info_label->style()->unpolish(email_info_label);
        email_info_label->style()->polish(email_info_label);
        email_info_label->update();
        datetime_info_label->setProperty("invalid", true);
        datetime_info_label->style()->unpolish(datetime_info_label);
        datetime_info_label->style()->polish(datetime_info_label);
        datetime_info_label->update();
    }
}
