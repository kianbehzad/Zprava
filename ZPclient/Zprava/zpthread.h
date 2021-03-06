#ifndef ZPTHREAD_H
#define ZPTHREAD_H

#include <QThread>
#include <QTimer>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QFile>
#include <QApplication>
#include <QTextStream>
#include "zpuser.h"
#include "zpglobals.h"

extern ZpUser* WHOAMI;

class ZpThread : public QThread
{
    Q_OBJECT
public:
    ZpThread();
    void run() override;
    QNetworkAccessManager* network;
    QNetworkRequest* request;
    QNetworkReply* reply;
    void handle_reply(QString reply_string);

public slots:
    void handle_timer();
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError err);
    void slotSslErrors(QList<QSslError> err);

public:
    QTimer* timer;
    QFile file;

signals:
    void updated();
    void is_connected(bool is_connected);

};

#endif // ZPTHREAD_H
