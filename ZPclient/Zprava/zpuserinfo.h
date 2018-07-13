#ifndef ZPUSERINFO_H
#define ZPUSERINFO_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QFile>
#include <QStyle>
#include "zpuser.h"

class ZpUserInfo : public QWidget
{
    Q_OBJECT
public:
    explicit ZpUserInfo(QString username ,QWidget *parent = 0);
    ZpUser* user;

private:
    //stylesheet
    QFile File;
    QString FormStyleSheet;
    //widget
    QLabel* photo_label;
    QPixmap* photo_map;
    QHBoxLayout* photo_lay;
    QWidget* photo_widg;
    QLabel* topic_label;
    QHBoxLayout* topic_lay;
    QWidget* topic_widg;
    QLabel* username_topic_label;
    QLabel* username_info_label;
    QGridLayout* username_lay;
    QWidget* username_widg;
    QLabel* email_topic_label;
    QLabel* email_info_label;
    QGridLayout* email_lay;
    QWidget* email_widg;
    QLabel* datetime_topic_label;
    QLabel* datetime_info_label;
    QGridLayout* datetime_lay;
    QWidget* datetime_widg;
    QVBoxLayout* info_lay;
    QWidget* info_widg;
    QPushButton* start_messaging_button;
    QHBoxLayout* start_messaging_lay;
    QWidget* start_messaging_widg;
    QVBoxLayout* form_lay;
    QWidget* form_widg;
    QHBoxLayout* lay;

signals:

private slots:
    void handle_update();
};

#endif // ZPUSERINFO_H
