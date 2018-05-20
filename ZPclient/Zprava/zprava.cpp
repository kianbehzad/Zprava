#include "zprava.h"
#include <QPushButton>
#include <QTextEdit>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QApplication>
#include <QFile>
#include <QString>
#include <QLatin1String>
#include <QDebug>
#include <QDir>
#include <QDebug>
#include <QDesktopWidget>



Zprava::Zprava(QWidget *parent)
    : QMainWindow(parent)
{
    //getting style sheets
    QFile File(":/stylesheet.qss");
    qDebug() << "is qt style sheet opend: " <<File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);


    //SIGNUP
    //top icon
    QLabel* signup_icon_label = new QLabel();
    signup_icon_label->setObjectName("icon_label");
    QPixmap* signup_icon_map = new QPixmap(":/signup.png");
    signup_icon_label->setPixmap(*signup_icon_map);
    signup_icon_label->setMaximumSize(100, 100);
    QHBoxLayout* signup_icon_lay = new QHBoxLayout();
    signup_icon_lay->addSpacing(200);
    signup_icon_lay->addWidget(signup_icon_label);
    signup_icon_lay->addSpacing(200);
    QWidget* signup_icon_widg = new QWidget();
    signup_icon_widg->setLayout(signup_icon_lay);

    //topic name
    QLabel* signup_topic_label = new QLabel();
    signup_topic_label->setText("SIGN UP");
    signup_topic_label->setObjectName("topic_label");
    QHBoxLayout* signup_topic_lay = new QHBoxLayout();
    signup_topic_lay->addSpacing(400);
    signup_topic_lay->addWidget(signup_topic_label);
    signup_topic_lay->addSpacing(400);
    QWidget* signup_topic_widg = new QWidget();
    signup_topic_widg->setLayout(signup_topic_lay);

    //inputs
    QLineEdit* signup_email_text = new QLineEdit();
    signup_email_text->setObjectName("input_text");
    signup_email_text->setPlaceholderText("Email Address");
    QLineEdit* signup_id_text = new QLineEdit();
    signup_id_text->setObjectName("input_text");
    signup_id_text->setPlaceholderText("User Id");
    QLineEdit* signup_pass_text = new QLineEdit();
    signup_pass_text->setEchoMode(QLineEdit::Password);
    signup_pass_text->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    signup_pass_text->setObjectName("input_text");
    signup_pass_text->setPlaceholderText("Password");

    //submit button
    QPushButton* signup_button = new QPushButton();
    signup_button->setObjectName("submit_button");
    signup_button->setText("Sign up");
    QHBoxLayout* signup_button_lay = new QHBoxLayout();
    signup_button_lay->addSpacing(400);
    signup_button_lay->addWidget(signup_button);
    signup_button_lay->addSpacing(400);
    QWidget* signup_button_widg = new QWidget();
    signup_button_widg->setLayout(signup_button_lay);

    //final form
    QVBoxLayout* signup_form_lay = new QVBoxLayout();
    signup_form_lay->addWidget(signup_icon_widg);
    signup_form_lay->addWidget(signup_topic_widg);
    signup_form_lay->addWidget(signup_email_text);
    signup_form_lay->addWidget(signup_id_text);
    signup_form_lay->addWidget(signup_pass_text);
    signup_form_lay->addWidget(signup_button_widg);
    QWidget* signup_form_widg = new QWidget();
    signup_form_widg->setObjectName("form_widg");
    signup_form_widg->setLayout(signup_form_lay);



    //LOGIN
    //top icon
    QLabel* login_icon_label = new QLabel();
    login_icon_label->setObjectName("icon_label");
    QPixmap* login_icon_map = new QPixmap(":/login.png");
    login_icon_label->setPixmap(*login_icon_map);
    login_icon_label->setMaximumSize(100, 100);
    QHBoxLayout* login_icon_lay = new QHBoxLayout();
    login_icon_lay->addSpacing(200);
    login_icon_lay->addWidget(login_icon_label);
    login_icon_lay->addSpacing(200);
    QWidget* login_icon_widg = new QWidget();
    login_icon_widg->setLayout(login_icon_lay);

    //topic name
    QLabel* login_topic_label = new QLabel();
    login_topic_label->setText("LOG IN");
    login_topic_label->setObjectName("topic_label");
    QHBoxLayout* login_topic_lay = new QHBoxLayout();
    login_topic_lay->addSpacing(400);
    login_topic_lay->addWidget(login_topic_label);
    login_topic_lay->addSpacing(400);
    QWidget* login_topic_widg = new QWidget();
    login_topic_widg->setLayout(login_topic_lay);

    //inputs
    QLineEdit* login_id_text = new QLineEdit();
    login_id_text->setObjectName("input_text");
    login_id_text->setPlaceholderText("User Id");
    QLineEdit* login_pass_text = new QLineEdit();
    login_pass_text->setEchoMode(QLineEdit::Password);
    login_pass_text->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    login_pass_text->setObjectName("input_text");
    login_pass_text->setPlaceholderText("Password");

    //submit button
    QPushButton* login_button = new QPushButton();
    login_button->setObjectName("submit_button");
    login_button->setText("Login");
    QHBoxLayout* login_button_lay = new QHBoxLayout();
    login_button_lay->addSpacing(400);
    login_button_lay->addWidget(login_button);
    login_button_lay->addSpacing(400);
    QWidget* login_button_widg = new QWidget();
    login_button_widg->setLayout(login_button_lay);

    //final form
    QVBoxLayout* login_form_lay = new QVBoxLayout();
    login_form_lay->addWidget(login_icon_widg);
    login_form_lay->addWidget(login_topic_widg);
    login_form_lay->addWidget(login_id_text);
    login_form_lay->addWidget(login_pass_text);
    login_form_lay->addWidget(login_button_widg);
    QWidget* login_form_widg = new QWidget();
    login_form_widg->setObjectName("form_widg");
    login_form_widg->setLayout(login_form_lay);


    //WHOLE FORM
    QHBoxLayout* whole_lay = new QHBoxLayout();
    whole_lay->addWidget(signup_form_widg);
    whole_lay->setSpacing(100);
    whole_lay->addWidget(login_form_widg);
    QWidget* whole_widg = new QWidget();
    whole_widg->setLayout(whole_lay);

    //set the whole form
    setCentralWidget(whole_widg);
    centralWidget()->setFixedSize(800, 480);



}

Zprava::~Zprava()
{

}
