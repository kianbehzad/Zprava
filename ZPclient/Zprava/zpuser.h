#ifndef ZPUSER_H
#define ZPUSER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QDateTime>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include "zpglobals.h"

extern qint64 TIMESPEC;

class ZpUser : public QObject
{
    Q_OBJECT
public:
    explicit ZpUser(QString _username, QObject *parent = 0);
    QString username;
    QString email;
    QDateTime last_message_datetime;

private:
    QNetworkAccessManager* network;
    QNetworkRequest* request;
    QNetworkReply* reply;
    void handle_reply(QString _reply);

private slots:
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError err);
    void slotSslErrors(QList<QSslError> err);

signals:
    void updated();
public slots:
};

#endif // ZPUSER_H
