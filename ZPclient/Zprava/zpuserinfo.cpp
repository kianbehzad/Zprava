#include "zpuserinfo.h"

ZpUserInfo::ZpUserInfo(QString _user, QWidget *parent) : QWidget(parent)
{
    apply_stylesheet();

    QFontDatabase::addApplicationFont(":/exo-regular.otf");
    QFont font_logo = QFont("Exo",15);


    user = new ZpUser(_user);
    grid_lay = new QGridLayout();
    start_chat_but = new QPushButton();
    user_username = new QLabel();
    user_email = new QLabel();
    email_label = new QLabel();
    username_label = new QLabel();
    user_photo_label = new QLabel();
    QImage img(":/login.png");
    QImage img2 = img.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    user_photo = new QPixmap();

    user_photo_label->setPixmap(QPixmap::fromImage(img2));

    user_username->setObjectName("user_username");
    user_email->setObjectName("user_email");
    email_label->setObjectName("email_label");
    username_label->setObjectName("username_label");
    user_photo_label->setObjectName("user_photo_label");



    username_label->setText("UserEmail: ");
    email_label->setText("Username: ");


    username_label->setFont(font_logo);
    email_label->setFont(font_logo);

    grid_lay->addWidget(user_photo_label,0,0,2,2);
    grid_lay->addWidget(username_label,0,3,1,1);
    grid_lay->addWidget(email_label,1,3,1,1);
    grid_lay->addWidget(user_email,1,4,1,5);
    grid_lay->addWidget(user_username,0,4,1,5);
    grid_lay->addWidget(start_chat_but,2,0,1,9);
    grid_lay->setSpacing(20);
    start_chat_but->setText("Start Chat");
    start_chat_but->setObjectName("start_chat_but");
    this->setLayout(grid_lay);


    QColor* color = new QColor("#b3b3cc");
    QPalette pal = palette();
    // set white background
    pal.setColor(QPalette::Background, *color );
    this->setAutoFillBackground(true);
    this->setPalette(pal);




    connect(user,SIGNAL(updated()),this,SLOT(show_widget()));
}

void ZpUserInfo::show_widget()
{
    qDebug()<<"Recievd";
    user_username->setText(user->email);
    user_email->setText(user->username);
    this->show();
}

void ZpUserInfo::apply_stylesheet()
{
    //getting style sheets
    File.setFileName(":/userinfo_stylesheet.qss");
    qDebug() << "is qt userinfo_stylesheet opend: " <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();

}
