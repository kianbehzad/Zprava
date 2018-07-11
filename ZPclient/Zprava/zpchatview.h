#ifndef ZPCHATVIEW_H
#define ZPCHATVIEW_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <QString>
#include <QApplication>
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include "zpuser.h"
#include "zpmessage.h"
#include "zptextmessage.h"

struct MessageHeaders{
    MessageHeaders(bool _amIPub, int _pk, ZpMessage::Type _type){amIPub = _amIPub; pk = _pk; type = _type;}
    bool amIPub; int pk; ZpMessage::Type type;
};

class ZpChatView_Thread : public QThread
{
    Q_OBJECT
public:
    ZpChatView_Thread(QString _username)
    {
        file.setFileName(qApp->applicationDirPath() + "/chats_data.json");
        username = _username;
    }
    void run() override
    {
        QJsonObject mine;
        QString file_data;
        bool is_opened = file.open(QFile::ReadOnly);
        if(is_opened)
            file_data = file.readAll();
        file.close();
        QJsonDocument document = QJsonDocument::fromJson(file_data.toUtf8());
        QJsonObject object = document.object();
        for(const auto& _username: object.keys())
            if(username == _username)
            {
                QJsonValue usr{ object[_username] };
                mine = usr.toObject();
            }
        QList<MessageHeaders> messageheaders;
        for(const auto& pk : mine.keys())
        {
            int Pk;
            bool amIPub;
            QString type;
            Pk = QString(pk).toInt();
            QJsonObject pkobj{ mine[pk].toObject() };
            for(const auto& item : pkobj)
            {
                if(item.isBool())
                    amIPub = item.toBool();
                if(item.isString())
                    type = item.toString();
            }
            if(type == "TEXT")
                messageheaders.push_back(MessageHeaders(amIPub, Pk, ZpMessage::Type::TEXT));
        }
        emit gotData(messageheaders);
    }

public:
    QFile file;
    QString username;

signals:
    void gotData(QList<MessageHeaders> messageheaders);

};

class ZpChatView : public QScrollArea
{
    Q_OBJECT
public:
    explicit ZpChatView(ZpUser* _opponent, QScrollArea *parent = 0);
    void add_message(ZpUser *_opponent, bool _amIpublisher, int _pk, ZpMessage::Type type);
    ZpMessage* get_message(int pk);
    void sort();
    QWidget* get_widget();

private slots:
    void handle_update();
    void handle_gotData(QList<MessageHeaders> messageheaders);
public slots:
    void updating();

private:
    //create ZpContactList widget
    ZpUser* opponent;
    QList<ZpMessage*> message_list;
    QVBoxLayout* messages_list_layout;
    QWidget* messages_list_widget;
    QWidget* filler;
    void resizeEvent(QResizeEvent*);
    ZpChatView_Thread* data_thread;

};

#endif // ZPCHATVIEW_H
