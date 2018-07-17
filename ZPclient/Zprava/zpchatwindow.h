#ifndef ZPCHATWINDOW_H
#define ZPCHATWINDOW_H

#include <QWidget>
#include <QScrollArea>
#include <QSplitter>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "zpcontactlist.h"
#include "zpnavigationbar.h"
#include "zpuserinfo.h"
#include "zpglobals.h"
#include "zpsettings.h"

struct ForwardInfo{
    ForwardInfo()
    {which_content = ""; origin_publisher = ""; message_data = "";}
    QString which_content; QString origin_publisher; QString message_data;
};


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
    QLabel* forward_descriptor;
    void keyPressEvent(QKeyEvent *e);
    ZpUserInfo* userinfo;
    //forward feature
    ForwardInfo forwardinfo;
    bool is_forward_proccess;
    QNetworkAccessManager* network;
    QNetworkRequest* request;
    QNetworkReply* reply;
    ZpSettings* settings;

signals:
    void logout();

public slots:
    void add_new_contact(bool);
    void user_info(QString username);
    void handle_contact_clicked(QString username);
    void handle_message_menu_trig(QString which_content, QString origin_publisher, QString message_data);
    void handle_setting_clicked();
    void handle_logout(bool);
};

#endif // ZPCHATWINDOW_H
