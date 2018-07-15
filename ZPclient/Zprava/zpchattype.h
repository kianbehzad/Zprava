#ifndef ZPCHATTYPE_H
#define ZPCHATTYPE_H

#include <QWidget>
#include<QGridLayout>
#include<QPushButton>
#include<QLabel>
#include<QTextEdit>
#include<QDebug>
#include<QTextCursor>
#include<QString>
#include<QPlainTextEdit>
#include<QPlainTextDocumentLayout>
#include<QGraphicsTextItem>
#include<QMargins>
#include<QSizeF>
#include<QLabel>
#include<QPixmap>
#include<QPalette>
#include<QMouseEvent>
#include<Qpixmap>
#include<QFile>
#include<QLatin1String>
#include<QSizePolicy>
#include<QFrame>
#include<QObject>
#include<iostream>
#include<string>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QTimerEvent>
#include<QTimer>
#include<QShortcut>
#include"zpuser.h"
#include "zpglobals.h"

extern ZpUser* WHOAMI;

class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();
signals:
    void clicked();

private:
    QPixmap* send_logo;
protected:
    void mousePressEvent(QMouseEvent* event);
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void hoverMove(QHoverEvent *event);
    bool event(QEvent *event);

};


class ZpChatType : public QWidget
{
    Q_OBJECT
public:
    explicit ZpChatType(ZpUser* opponent,QWidget *parent = 0);
    int type_height;
    void apply_stylesheet();
    void initial_networking_navigationbar(QString);
    QGridLayout* get_layout();
private:
    QGridLayout* type_lay;
    ClickableLabel* send_but;
    QLabel* failure_logo;
    QTextEdit* type;
    QTextCursor* cursor;
    QSizeF documentSize;
    QMargins margins;
    QFile File;
    QString FormStyleSheet;
    QNetworkAccessManager* chat_network;
    QNetworkRequest* chat_request;
    QNetworkReply* chat_reply;
    QPixmap* failure_pic;
    QTimer* timer;
    QShortcut* shortcut;
    ZpUser* opponent;
    int height;
    int lines_num;
    int line_nums_before;
private:
    void handle_reply(QString _reply);




signals:
    void increment_size();
    void decrement_size();


public slots:
    void add_size();
    void minus_size();
    void but_callback();
    void check_size();
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError err);
    void slotSslErrors(QList<QSslError> err);
    void fade_failure();

private slots:
    virtual void keyReleaseEvent(QKeyEvent*) override;
};



#endif // ZPCHATTYPE_H
