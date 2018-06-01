#include "zprava.h"




Zprava::Zprava(QWidget *parent)
    : QMainWindow(parent)
{
    //resizing main window
    int width{1280}, height{939};
    if(QApplication::desktop()->availableGeometry().width() < 1280)
        width = QApplication::desktop()->availableGeometry().width();
    if(QApplication::desktop()->availableGeometry().height() < 939)
        height = QApplication::desktop()->availableGeometry().height();
    setMaximumSize(width, height);//setFixedSize(width, height);

    //stylesheet
    apply_stylesheet();

    //add form into main window
    form = new ZpForm(true);
    QHBoxLayout* lay = new QHBoxLayout();
    form->setMaximumSize(2*width/3, 2*height/3);//form->setFixedSize(2*width/3, 2*height/3);
    lay->addWidget(form);
    QWidget* w = new QWidget(this);
    w->setLayout(lay);
    setCentralWidget(w);

    //chatwindow
    connect(form, SIGNAL(login_validate(QString,QString)), this, SLOT(SLOTlogin_validate(QString,QString)));


}

Zprava::~Zprava()
{

}

void Zprava::apply_stylesheet()
{
    //getting style sheets
    File.setFileName(":/qApp_stylesheet.qss");
    qDebug() << "is qt qApp_stylesheet opend: " <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();
}

void Zprava::SLOTlogin_validate(QString username, QString password)
{
    QLabel* information = new QLabel();
    information->setText("your username is\n: " + username);
    information->setFixedSize(400, 400);
    information->setAlignment(Qt::AlignCenter);
    QHBoxLayout* information_lay = new QHBoxLayout();
    information_lay->addWidget(information);
    QWidget* information_widg = new QWidget();
    information_widg->setLayout(information_lay);
    this->setCentralWidget(information_widg);
    this->setStyleSheet("Zprava{background-image:url(\":/chatwindow.png\"); background-position: center;}QLabel{background-color: rgba(10%, 20%, 15%, 75%);color: white;font: 50pt 'Arial';text-align:center;border-radius: 48px;}");

}
