#ifndef ZPWINDOW_H
#define ZPWINDOW_H

#include <QSplitter>
#include <QGridLayout>
#include <QWidget>
#include <QObject>
#include <QFile>
#include <QString>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "zpcontactlist.h"
#include "zpuser.h"

extern ZpUser* WHOAMI;

class ZpWindow : public QSplitter
{
    Q_OBJECT
public:
    ZpWindow(QSplitter* parent = 0);
    ZpContactList* contactlist;

private:
    QSplitter* splitter;
    QGridLayout* right_lay;
    QWidget* right_widg;
    QWidget* chatview;
    QWidget* sender;
    QFile file;
    QString file_data;

public slots:
    void handle_threadUpdate();

signals:
    void thread_updateStep2();
};

#endif // ZPWINDOW_H
