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
    setFixedSize(width, height);

    //stylesheet
    apply_stylesheet();

    //add form into main window
    form = new ZpForm(true);
    QHBoxLayout* lay = new QHBoxLayout();
    form->setFixedSize(2*width/3, 2*height/3);
    lay->addWidget(form);
    QWidget* w = new QWidget(this);
    w->setLayout(lay);
    setCentralWidget(w);


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
