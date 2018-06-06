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
#include <utility>

using namespace std::rel_ops;

class ZpContact : public QWidget
{
    Q_OBJECT
public:
    explicit ZpContact(QWidget *parent = 0);
    //ZpContact Widget public
    QLabel* contact;
    QLabel* icon;
    //notification functions
    void set_notification();
    void remove_notification();
    void set_muted()   {is_muted = true;}
    void set_unmuted() {is_muted = false;}
    //date and time function//which one is earlier is smaller
    void set_datetime(int year, int month, int day, int hour, int minute, int second);
    bool operator<(const ZpContact& op) const;
    bool operator==(const ZpContact& op) const;

private:
    //STYLESHEET
    QFile File;
    QString FormStyleSheet;
    //ZpContact Widgets private
    QGridLayout* grid_lay;
    //notification
    QPixmap* icon_map;
    bool is_muted = false;
    //date and time
    QDateTime* datetime;

signals:
    void clicked(QString user);

public slots:

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // ZPCONTACT_H
