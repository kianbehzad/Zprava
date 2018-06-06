#ifndef ZPCONTACTLIST_H
#define ZPCONTACTLIST_H

#include <QWidget>
#include <QList>
#include <QVBoxLayout>
#include <QScrollArea>
#include "zpcontact.h"

class ZpContactList : public QScrollArea
{
    Q_OBJECT
public:
    explicit ZpContactList(QScrollArea *parent = 0);
    void add_contact(QString username);

private:
    //create ZpContactList widget
    QList<ZpContact*> contacts_list;
    QVBoxLayout* contacts_list_layout;
    QWidget* contact_list_widget;

signals:

public slots:
};

#endif // ZPCONTACTLIST_H
