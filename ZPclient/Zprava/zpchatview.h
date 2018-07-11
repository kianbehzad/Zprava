#ifndef ZPCHATVIEW_H
#define ZPCHATVIEW_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include "zpuser.h"
#include "zpmessage.h"
#include "zptextmessage.h"

class ZpChatView : public QScrollArea
{
    Q_OBJECT
public:
    explicit ZpChatView(ZpUser* _opponent, QScrollArea *parent = 0);
    void add_message(ZpUser *_opponent, bool _amIpublisher, int _pk, ZpMessage::Type type);
    ZpMessage* get_message(int pk);
    void sort();

private slots:
    void handle_update();

private:
    //create ZpContactList widget
    ZpUser* opponent;
    QList<ZpMessage*> message_list;
    QVBoxLayout* messages_list_layout;
    QWidget* messages_list_widget;
    QWidget* filler;
    void resizeEvent(QResizeEvent*);
};

#endif // ZPCHATVIEW_H
