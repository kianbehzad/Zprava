#ifndef ZPMESSAGE_H
#define ZPMESSAGE_H

#include <QObject>
#include <QDateTime>
#include <QWidget>
#include "zpuser.h"
#include "zpglobals.h"

extern ZpUser* WHOAMI;

class ZpMessage : public QWidget
{
    Q_OBJECT
public:
    enum class Type
    {
        TEXT = 0,
        PHOTO = 1,
        AUDIO = 2,
        VIDEO = 3
    };
    explicit ZpMessage(ZpUser* _opponent, bool _amIpublisher, int _pk, QWidget *parent = 0);
    int widget_height;
    int widget_width;
    ZpUser* opponent;
    bool amIpublisher;
    QDateTime datetime;
    bool is_seen;
    Type type;
    int pk;

protected:
    QNetworkAccessManager* network;
    QNetworkRequest* request;
    QNetworkReply* reply;
    virtual void handle_reply(QString _reply) = 0;

protected slots:
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError err);
    void slotSslErrors(QList<QSslError> err);
    virtual void updating() = 0;

signals:
    void updated();

public slots:
};

#endif // ZPMESSAGE_H
