#include "zpform.h"

ZpForm::ZpForm(QWidget *parent) : QWidget(parent)
{
    //getting style sheets
    File.setFileName(":/form_stylesheet.qss");
    qDebug() << "is qt form_stylesheet opend: " <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(FormStyleSheet);


    //SIGNUP
    //top icon
    signup_icon_label = new QLabel();
    signup_icon_label->setObjectName("icon_label");
    signup_icon_map = new QPixmap(":/signup.png");
    signup_icon_label->setPixmap(*signup_icon_map);
    signup_icon_label->setMaximumSize(100, 100);
    signup_icon_lay = new QHBoxLayout();
    signup_icon_lay->addSpacing(200);
    signup_icon_lay->addWidget(signup_icon_label);
    signup_icon_lay->addSpacing(200);
    signup_icon_widg = new QWidget();
    signup_icon_widg->setLayout(signup_icon_lay);

    //topic name
    signup_topic_label = new QLabel();
    signup_topic_label->setText("SIGN UP");
    signup_topic_label->setObjectName("topic_label");
    signup_topic_lay = new QHBoxLayout();
    signup_topic_lay->addSpacing(400);
    signup_topic_lay->addWidget(signup_topic_label);
    signup_topic_lay->addSpacing(400);
    signup_topic_widg = new QWidget();
    signup_topic_widg->setLayout(signup_topic_lay);

    //inputs
    signup_email_text = new QLineEdit();
    signup_email_text->setObjectName("input_text");
    signup_email_text->setPlaceholderText("Email Address");
    signup_id_text = new QLineEdit();
    signup_id_text->setObjectName("input_text");
    signup_id_text->setPlaceholderText("User Id");
    signup_pass_text = new QLineEdit();
    signup_pass_text->setEchoMode(QLineEdit::Password);
    signup_pass_text->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    signup_pass_text->setObjectName("input_text");
    signup_pass_text->setPlaceholderText("Password");

    //submit button
    signup_button = new QPushButton();
    signup_button->setObjectName("submit_button");
    signup_button->setText("Sign up");
    signup_button_lay = new QHBoxLayout();
    signup_button_lay->addSpacing(400);
    signup_button_lay->addWidget(signup_button);
    signup_button_lay->addSpacing(400);
    signup_button_widg = new QWidget();
    signup_button_widg->setLayout(signup_button_lay);

    //final form
    signup_form_lay = new QVBoxLayout();
    signup_form_lay->addWidget(signup_icon_widg);
    signup_form_lay->addWidget(signup_topic_widg);
    signup_form_lay->addWidget(signup_email_text);
    signup_form_lay->addWidget(signup_id_text);
    signup_form_lay->addWidget(signup_pass_text);
    signup_form_lay->addWidget(signup_button_widg);
    signup_form_widg = new QWidget();
    signup_form_widg->setObjectName("form_widg");
    signup_form_widg->setLayout(signup_form_lay);



    //LOGIN
    //top icon
    login_icon_label = new QLabel();
    login_icon_label->setObjectName("icon_label");
    login_icon_map = new QPixmap(":/login.png");
    login_icon_label->setPixmap(*login_icon_map);
    login_icon_label->setMaximumSize(100, 100);
    login_icon_lay = new QHBoxLayout();
    login_icon_lay->addSpacing(200);
    login_icon_lay->addWidget(login_icon_label);
    login_icon_lay->addSpacing(200);
    login_icon_widg = new QWidget();
    login_icon_widg->setLayout(login_icon_lay);

    //topic name
    login_topic_label = new QLabel();
    login_topic_label->setText("LOG IN");
    login_topic_label->setObjectName("topic_label");
    login_topic_lay = new QHBoxLayout();
    login_topic_lay->addSpacing(400);
    login_topic_lay->addWidget(login_topic_label);
    login_topic_lay->addSpacing(400);
    login_topic_widg = new QWidget();
    login_topic_widg->setLayout(login_topic_lay);

    //inputs
    login_id_text = new QLineEdit();
    login_id_text->setObjectName("input_text");
    login_id_text->setPlaceholderText("User Id");
    login_pass_text = new QLineEdit();
    login_pass_text->setEchoMode(QLineEdit::Password);
    login_pass_text->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    login_pass_text->setObjectName("input_text");
    login_pass_text->setPlaceholderText("Password");

    //submit button
    login_button = new QPushButton();
    login_button->setObjectName("submit_button");
    login_button->setText("Login");
    login_button_lay = new QHBoxLayout();
    login_button_lay->addSpacing(400);
    login_button_lay->addWidget(login_button);
    login_button_lay->addSpacing(400);
    login_button_widg = new QWidget();
    login_button_widg->setLayout(login_button_lay);

    //final form
    login_form_lay = new QVBoxLayout();
    login_form_lay->addWidget(login_icon_widg);
    login_form_lay->addWidget(login_topic_widg);
    login_form_lay->addWidget(login_id_text);
    login_form_lay->addWidget(login_pass_text);
    login_form_lay->addWidget(login_button_widg);
    login_form_widg = new QWidget();
    login_form_widg->setObjectName("form_widg");
    login_form_widg->setLayout(login_form_lay);


    //WHOLE FORM
    whole_lay = new QHBoxLayout();
    whole_lay->addWidget(signup_form_widg);
    whole_lay->setSpacing(100);
    whole_lay->addWidget(login_form_widg);
    this->setLayout(whole_lay);
}