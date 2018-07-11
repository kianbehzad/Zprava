#include "zprava.h"
#include <QList>
#include <QString>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Zprava w;
    //centering the main window
    QRect r = w.geometry();
    r.moveCenter(QApplication::desktop()->availableGeometry().center());
    w.setGeometry(r);
    w.show();

    //signal registration
    qRegisterMetaType<QList<QString>>("QList<QString>");

    return a.exec();
}
