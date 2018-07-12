#ifndef ZPCHATWINDOW_H
#define ZPCHATWINDOW_H

#include <QWidget>
#include <QScrollArea>
#include <QSplitter>
#include <QGridLayout>
#include <QHBoxLayout>
#include "zpcontactlist.h"

class ZpChatWindow : public QSplitter
{
    Q_OBJECT
public:
    explicit ZpChatWindow(QWidget *parent = 0);
    ZpContactList* contactlist;

private:
    //STYLESHEET
    QFile File;
    QString FormStyleSheet;
    //WIDGET
    QGridLayout* right_lay;
    QWidget* right_widg;
    QWidget* chatview_holder;
    QWidget* chattype_holder;
    QWidget* prev;


signals:

public slots:
    void handle_contact_clicked(QString username);
};

#endif // ZPCHATWINDOW_H
