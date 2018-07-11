#ifndef ZPCONTACT_H
#define ZPCONTACT_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QPixmap>
#include <QDateTime>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QImage>
#include <QStyle>
#include "zpuser.h"

class ZpContact : public QWidget
{
    Q_OBJECT
public:
    explicit ZpContact(QString username, QWidget *parent = 0);
    ZpUser* user;
    //ZpContact Widget public
    QLabel* picture;
    QLabel* title;
    QLabel* notification;
    QLabel* datetime;
    //notification functions
    void set_notification();
    void remove_notification();
    void set_muted();
    void set_unmuted();
    void set_focused(bool isFocused);
    static const int Height = 70;


private:
    //STYLESHEET
    QFile File;
    QString FormStyleSheet;
    //ZpContact Widgets private
    QGridLayout* grid;
    QPixmap* notification_map;
    //notification
    bool is_muted = false;
    bool has_notification;
    //context menu
    QMenu* context_menu;
    QAction* menu_set_muted;
    QAction* menu_set_unmuted;


signals:
    void clicked(QString user);

private slots:
    void slot_menu_triggered(QAction*menu_action);
    void handle_update();
public slots:
    void updating();
protected:
    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // ZPCONTACT_H
