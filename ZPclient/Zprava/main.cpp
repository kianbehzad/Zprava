#include "zprava.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Zprava w;
    //resizing and replacing window
////    int width{1280}, height{939};
////    if(QApplication::desktop()->availableGeometry().width() < 1280)
////        width = QApplication::desktop()->availableGeometry().width();
////    if(QApplication::desktop()->availableGeometry().height() < 939)
////        height = QApplication::desktop()->availableGeometry().height();
    w.setFixedSize(800, 480);
    QRect r = w.geometry();
    //qDebug() << w.geometry().width() << w.geometry().height();
    r.moveCenter(QApplication::desktop()->availableGeometry().center());
    w.setGeometry(r);
    w.show();

    return a.exec();
}
