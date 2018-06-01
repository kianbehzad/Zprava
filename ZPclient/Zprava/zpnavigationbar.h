#ifndef ZPNAVIGATIONBAR_H
#define ZPNAVIGATIONBAR_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QApplication>
#include <QFile>
#include <QString>
#include <QLatin1String>
#include <QDebug>
#include <QDir>
#include <QDebug>
#include <QDesktopWidget>

class ZpNavigationBar : public QWidget
{
    Q_OBJECT
public:
    explicit ZpNavigationBar(QWidget *parent = 0);
private:
    //STYLESHEET
    void apply_stylesheet();
    QFile File;
    QString FormStyleSheet;

private:
    //NAVIGATION BAR GRAPHICAL USER INTERFACE
    QLabel* nav_icon_label;
    QPixmap* nav_icon_map;
    QHBoxLayout* nav_icon_lay;
    QWidget* nav_icon_widg;
    QLabel* nav_status_label;
    QHBoxLayout* nav_status_lay;
    QWidget* nav_status_widg;
    QPushButton* nav_back_button;
    QHBoxLayout* nav_back_lay;
    QWidget* nav_back_widg;
    //WHOLE NAV LAY
    QHBoxLayout* whole_lay;
    void create_form_navigation_widget();

signals:

public slots:
};

#endif // ZPNAVIGATIONBAR_H
