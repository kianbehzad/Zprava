#ifndef ZPCONTACTLIST_H
#define ZPCONTACTLIST_H

#include <QWidget>
#include <QList>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QResizeEvent>
#include "zpcontact.h"

class ZpContactList : public QScrollArea
{
    Q_OBJECT
public:
    explicit ZpContactList(QScrollArea *parent = 0);
    void add_contact(ZpUser *user);
    ZpContact* get_contact(QString username);
    void sort();

private slots:
    void handle_update();

private:
    //create ZpContactList widget
    QList<ZpContact*> contacts_list;
    QVBoxLayout* contacts_list_layout;
    QWidget* contact_list_widget;
    QWidget* filler;
    void resizeEvent(QResizeEvent*);

signals:

public slots:
    void handle_clicked(QString username);
};

#endif // ZPCONTACTLIST_H
