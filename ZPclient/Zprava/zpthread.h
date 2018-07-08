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


class ZpThread : public QThread
{
    Q_OBJECT
public:
    ZpThread(QString _username);
    QString username;
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

};

#endif // ZPTHREAD_H
