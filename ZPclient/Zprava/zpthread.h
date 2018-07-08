#ifndef ZPTHREAD_H
#define ZPTHREAD_H

#include <QThread>
#include <QTimer>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

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

public slots:
    void handle_timer();
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError err);
    void slotSslErrors(QList<QSslError> err);

public:
    bool getallchats;
    QTimer* timer;


};

#endif // ZPTHREAD_H
