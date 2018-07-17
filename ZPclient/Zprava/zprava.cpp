#include "zprava.h"

ZpUser* WHOAMI;
qint64 TIMESPEC = 60*60*4.5;


Zprava::Zprava(QWidget *parent)
    : QMainWindow(parent)
{
    //resizing main window
    _width = 1280;
    _height = 939;
    if(QApplication::desktop()->availableGeometry().width() < 1280)
        _width = QApplication::desktop()->availableGeometry().width();
    if(QApplication::desktop()->availableGeometry().height() < 939)
        _height = QApplication::desktop()->availableGeometry().height();
    setMaximumSize(_width, _height);//setFixedSize(width, height);

    //change to ::FALSE:: for experimental mode
    if(true)
    {
        //production mode
        //stylesheet
        apply_stylesheet();

        //add form into main window
        form = new ZpForm(true);
        connect(form, SIGNAL(login_validate(QString,QString)), this, SLOT(login(QString,QString)));
        QHBoxLayout* lay = new QHBoxLayout();
        form->setMaximumSize(2*_width/3, 2*_height/3);//form->setFixedSize(2*width/3, 2*height/3);
        lay->addWidget(form);
        w = new QWidget(this);
        w->setLayout(lay);
        setCentralWidget(w);
        connection = new QLabel();
        connection->setContentsMargins(10, 5, 10, 5);
        connection->setGeometry(0, this->height()-30, 100, 30);
        connection->setText("connecting...");
        connection->setStyleSheet("background-color: rgba(102, 102, 153, 0.5); color: red;");
    }
    else
    {
        //experimental mode
        experiment = new ZpExperimental(this);
        setCentralWidget(experiment);
    }


}

Zprava::~Zprava()
{

}

void Zprava::apply_stylesheet()
{
    //getting style sheets
    File.setFileName(":/qApp_stylesheet.qss");
    qDebug() << "is qt qApp_stylesheet opend:" <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();
}

void Zprava::login(QString username, QString password)
{
    WHOAMI = new ZpUser(username);
    thread = new ZpThread();
    chatwindow = new ZpChatWindow(this);
    connect(thread, SIGNAL(updated()), chatwindow->contactlist, SLOT(updating()));
    connect(thread, SIGNAL(is_connected(bool)), this, SLOT(handle_is_connected(bool)));
    connect(chatwindow, SIGNAL(logout()), this, SLOT(handle_logout()));
    thread->start();
    setCentralWidget(chatwindow);
}

void Zprava::handle_is_connected(bool is_connected)
{
    if(is_connected)
    {
        connection->hide();
        return;
    }
    //else
    connection->setParent(chatwindow);
    connection->setGeometry(0, this->height()-30, 100, 30);
    connection->show();
}

void Zprava::handle_logout()
{
    QFile login_data;
    login_data.setFileName(qApp->applicationDirPath() + "/login_data.txt");
    login_data.remove();
    form = new ZpForm(true);
    connect(form, SIGNAL(login_validate(QString,QString)), this, SLOT(login(QString,QString)));
    QHBoxLayout* lay = new QHBoxLayout();
    form->setMaximumSize(2*_width/3, 2*_height/3);//form->setFixedSize(2*width/3, 2*height/3);
    lay->addWidget(form);
    w = new QWidget(this);
    w->setLayout(lay);
    setCentralWidget(w);
}
