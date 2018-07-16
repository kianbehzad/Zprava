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
#include "zpglobals.h"


struct MessageHeaders{
    MessageHeaders(bool _amIPub, int _pk, ZpMessage::Type _type, bool _is_seen){amIPub = _amIPub; pk = _pk; type = _type; is_seen = _is_seen;}
    bool amIPub; int pk; ZpMessage::Type type; bool is_seen;
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
        new_messageheaders.clear();
        deleted_messageheaders.clear();
        for(const auto& pk : mine.keys())
        {
            int Pk;
            bool amIPub;
            QString type;
            bool is_seen;
            Pk = QString(pk).toInt();
            QJsonObject pkobj{ mine[pk].toObject() };
            for(const auto& item : pkobj)
            {
                if(item.isBool())
                    amIPub = item.toBool();
                if(item.isString())
                    type = item.toString();
                if(item.isDouble())
                    is_seen = static_cast<bool>(item.toDouble());
            }
            if(type == "TEXT")
                new_messageheaders.push_back(MessageHeaders(amIPub, Pk, ZpMessage::Type::TEXT, is_seen));
        }
        if(!new_messageheaders.isEmpty())
        {
            for(const auto& last: last_messageheaders)
            {
                bool exist{false};
                for(const auto& _new: new_messageheaders)
                    if(last.pk == _new.pk)
                        exist = true;
                if(!exist)
                    deleted_messageheaders.push_back(last);
            }
            last_messageheaders.clear();
            last_messageheaders = new_messageheaders;
        }
        emit gotData(new_messageheaders, deleted_messageheaders);
    }

public:
    QFile file;
    QString username;
    QList<MessageHeaders> new_messageheaders;
    QList<MessageHeaders> last_messageheaders;
    QList<MessageHeaders> deleted_messageheaders;

signals:
    void gotData(QList<MessageHeaders> messageheaders, QList<MessageHeaders> deleted);

};

class ZpChatView : public QScrollArea
{
    Q_OBJECT
public:
    explicit ZpChatView(ZpUser* _opponent, QScrollArea *parent = 0);
    void add_message(ZpUser *_opponent, bool _amIpublisher, int _pk, ZpMessage::Type type, bool is_seen);
    ZpMessage* get_message(int pk);
    void sort();
    QWidget* get_widget();
    QList<ZpMessage*> message_list;

private slots:
    void handle_update();
    void handle_gotData(QList<MessageHeaders> messageheaders, QList<MessageHeaders> deleted);
public slots:
    void updating();
    void handle_message_menu_trig(QString which_content, QString publisher, QString message_data);

private:
    //create ZpContactList widget
    ZpUser* opponent;
    QVBoxLayout* messages_list_layout;
    QWidget* messages_list_widget;
    QWidget* filler;
    void resizeEvent(QResizeEvent*);
    ZpChatView_Thread* data_thread;

signals:
    void trig_Message();
    void message_menu_trig(QString which_content, QString publisher, QString message_data);

};

#endif // ZPCHATVIEW_H
