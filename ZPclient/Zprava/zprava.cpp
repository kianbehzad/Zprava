#include "zprava.h"
#include <QHBoxLayout>




Zprava::Zprava(QWidget *parent)
    : QMainWindow(parent)
{
    //SET THE FORM
    //resizing main window
    int width{1280}, height{939};
    if(QApplication::desktop()->availableGeometry().width() < 1280)
        width = QApplication::desktop()->availableGeometry().width();
    if(QApplication::desktop()->availableGeometry().height() < 939)
        height = QApplication::desktop()->availableGeometry().height();
    setFixedSize(width, height);
    //add form into main window
    chat = new zpchatwindow();
    QHBoxLayout* lay = new QHBoxLayout();
    chat->setFixedSize(2*width/3, 2*height/3);
    lay->addWidget(chat);
    QWidget* w = new QWidget(this);
    w->setLayout(lay);
    setCentralWidget(chat);


}

Zprava::~Zprava()
{

}
