#ifndef ZPMESSAGE_H
#define ZPMESSAGE_H

#include <QObject>
#include <QDateTime>
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
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
    ZpUser* origin_publisher;
    bool is_forward;
    bool amIpublisher;
    QDateTime datetime;
    bool is_seen;
    Type type;
    int pk;
    //context menu
    QMenu* context_menu;
    QAction* menu_forward;

protected:
    QNetworkAccessManager* network;
    QNetworkRequest* request;
    QNetworkReply* reply;
    virtual void handle_reply(QString _reply) = 0;
    void mousePressEvent(QMouseEvent* event);


protected slots:
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError err);
    void slotSslErrors(QList<QSslError> err);
    virtual void updating() = 0;
    virtual void slot_menu_triggered(QAction*) = 0;


signals:
    void updated();
    void message_menu_trig(QString which_content, QString publisher, QString message_data);

public slots:
};

#endif // ZPMESSAGE_H
