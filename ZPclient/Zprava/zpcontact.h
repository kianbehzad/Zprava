#ifndef ZPCONTACT_H
#define ZPCONTACT_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QPixmap>

class ZpContact : public QWidget
{
    Q_OBJECT
public:
    explicit ZpContact(QWidget *parent = 0);
    //STYLESHEET
    QFile File;
    QString FormStyleSheet;
    //ZpContact Widgets
    QGridLayout* grid_lay;
    QLabel* contact;
    QLabel* icon;
    //notification
    QPixmap* icon_map;
    bool is_muted = false;
    //functions
    void set_notification();
    void remove_notification();
    void set_muted()   {is_muted = true;}
    void set_unmuted() {is_muted = false;}

signals:

public slots:
};

#endif // ZPCONTACT_H
