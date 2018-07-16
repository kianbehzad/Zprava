#ifndef ZPCONTACTLIST_H
#define ZPCONTACTLIST_H

#include <QWidget>
#include <QList>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QResizeEvent>
#include <QThread>
#include <QApplication>
#include "zpcontact.h"
#include "zpglobals.h"

class ZpContactList_Thread : public QThread
{
    Q_OBJECT
public:
    ZpContactList_Thread()
    {
        file.setFileName(qApp->applicationDirPath() + "/chats_data.json");
    }
    void run() override
    {
        bool is_opened = file.open(QFile::ReadOnly);
        //qDebug() << "is chats_data: " << is_opened;
        QString file_data;
        if(is_opened)
            file_data = file.readAll();
        file.close();
        QJsonDocument document = QJsonDocument::fromJson(file_data.toUtf8());
        QJsonObject object = document.object();
        new_contacts.clear();
        deleted_contacts.clear();
        for(const auto& username: object.keys())
            new_contacts.push_back(username);
        if(!new_contacts.isEmpty())
        for(const auto& last: last_contacts)
        {
            bool exist{false};
            for(const auto& _new: new_contacts)
                if(last == _new)
                    exist = true;
            if(!exist)
                deleted_contacts.push_back(last);
        }
        last_contacts.clear();
        last_contacts = new_contacts;
        emit gotData(new_contacts, deleted_contacts);
    }

public:
    QFile file;
    QList<QString> new_contacts;
    QList<QString> last_contacts;
    QList<QString> deleted_contacts;

signals:
    void gotData(QList<QString> username, QList<QString> deleted);

};

class ZpContactList : public QScrollArea
{
    Q_OBJECT
public:
    explicit ZpContactList(QScrollArea *parent = 0);
    void add_contact(QString username);
    ZpContact* get_contact(QString username);
    void sort();

private slots:
    void handle_update();
    void handle_gotData(QList<QString> username, QList<QString> deleted);
public slots:
    void updating();

private:
    //create ZpContactList widget
    QList<ZpContact*> contacts_list;
    QVBoxLayout* contacts_list_layout;
    QWidget* contact_list_widget;
    QWidget* filler;
    void resizeEvent(QResizeEvent*);
    ZpContactList_Thread* data_thread;

signals:
    void trig_ZpContact();
    void contact_clicked(QString username);
    void message_menu_trig(QString which_content, QString publisher, QString message_data);

public slots:
    void handle_clicked(QString username);
    void handle_message_menu_trig(QString which_content, QString publisher, QString message_data);
};

#endif // ZPCONTACTLIST_H
