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
        QList<QString> contacts;
        for(const auto& username: object.keys())
            contacts.push_back(username);
        emit gotData(contacts);
    }

public:
    QFile file;

signals:
    void gotData(QList<QString> username);

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
    void handle_gotData(QList<QString> contacts);
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

public slots:
    void handle_clicked(QString username);
};

#endif // ZPCONTACTLIST_H
