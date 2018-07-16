#ifndef ZPSETTINGS_H
#define ZPSETTINGS_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QFile>
#include <QStyle>
#include "zpuser.h"
#include "zpglobals.h"

extern ZpUser* WHOAMI;

class ZpSettings : public QWidget
{
    Q_OBJECT
public:
    explicit ZpSettings(QWidget *parent = 0);

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
    QVBoxLayout* info_lay;
    QWidget* info_widg;
    QPushButton* change_username_button;
    QPushButton* change_password_button;
    QPushButton* logout_button;
    QGridLayout* buttons_lay;
    QWidget* buttons_widg;
    QVBoxLayout* form_lay;
    QWidget* form_widg;
    QHBoxLayout* lay;


signals:

public slots:
};

#endif // ZPSETTINGS_H
