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
}
