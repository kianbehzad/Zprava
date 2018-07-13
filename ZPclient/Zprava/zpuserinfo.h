#ifndef ZPUSERINFO_H
#define ZPUSERINFO_H
#include<QWidget>
#include "zpuser.h"
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QColor>
#include <QPixmap>
#include<QString>
#include<QFile>
#include<QString>
#include<QFont>
#include<QColor>
#include<QFontDatabase>
#include<QPalette>
#include<QColor>
#include<QImage>

class ZpUserInfo : public QWidget
{
    Q_OBJECT
public:
    explicit ZpUserInfo(QString ,QWidget *parent = 0);
    QPushButton* start_chat_but;
    void apply_stylesheet();

private:
    ZpUser* user;
    QGridLayout* grid_lay;
    QLabel* user_photo_label;
    QPixmap* user_photo;
    QLabel* user_username;
    QLabel* user_email;
    QLabel* email_label;
    QLabel* username_label;
    QFile File;
    QString FormStyleSheet;


signals:

public slots:
    void show_widget();
};

#endif // ZPUSERINFO_H
