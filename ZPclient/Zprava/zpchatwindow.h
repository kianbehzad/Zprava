#ifndef ZPCHATWINDOW_H
#define ZPCHATWINDOW_H

#include <QWidget>
#include <QScrollArea>
#include <QSplitter>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QKeyEvent>
#include "zpcontactlist.h"
#include "zpnavigationbar.h"
#include "zpuserinfo.h"

class ZpChatWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ZpChatWindow(QWidget *parent = 0);
    ZpContactList* contactlist;
    ZpNavigationBar* navigationbar;

private:
    //STYLESHEET
    QFile File;
    QString FormStyleSheet;
    //WIDGET
    QVBoxLayout* whole_lay;
    QGridLayout* right_lay;
    QSplitter* splitter;
    QWidget* right_widg;
    QWidget* chatview_holder;
    QWidget* chattype_holder;
    QWidget* prev_chatview;
    QWidget* prev_chattype;
    void keyPressEvent(QKeyEvent *e);

signals:

public slots:
    void user_info(QString username);
    void handle_contact_clicked(QString username);
};

#endif // ZPCHATWINDOW_H
