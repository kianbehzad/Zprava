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
#include <utility>

using namespace std::rel_ops;

class ZpContact : public QWidget
{
    Q_OBJECT
public:
    explicit ZpContact(QString username, QWidget *parent = 0);
    //ZpContact Widget public
    QLabel* contact;
    QLabel* icon;
    //notification functions
    void set_notification();
    void remove_notification();
    void set_muted();
    void set_unmuted();
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
    bool has_notification;
    //date and time
    QDateTime* datetime;
    //context menu
    QMenu* context_menu;
    QAction* menu_set_muted;
    QAction* menu_set_unmuted;


signals:
    void clicked(QString user);

private slots:
    void slot_menu_triggered(QAction*menu_action);
protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // ZPCONTACT_H
