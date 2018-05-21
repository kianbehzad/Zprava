#ifndef ZPRAVA_H
#define ZPRAVA_H

#include <QMainWindow>
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


class Zprava : public QMainWindow
{
    Q_OBJECT

public:
    Zprava(QWidget *parent = 0);
    ~Zprava();
//GUI
public:
    //STYLESHEET
    QFile File;
    QString StyleSheet;
    //SIGNUP FORM WIDGETS
    QLabel* signup_icon_label;
    QPixmap* signup_icon_map;
    QHBoxLayout* signup_icon_lay;
    QWidget* signup_icon_widg;
    QLabel* signup_topic_label;
    QHBoxLayout* signup_topic_lay;
    QWidget* signup_topic_widg;
    QLineEdit* signup_email_text;
    QLineEdit* signup_id_text;
    QLineEdit* signup_pass_text;
    QPushButton* signup_button;
    QHBoxLayout* signup_button_lay;
    QWidget* signup_button_widg;
    QVBoxLayout* signup_form_lay;
    QWidget* signup_form_widg;
    //LOGIN FORM WIDGETS
    QLabel* login_icon_label;
    QPixmap* login_icon_map;
    QHBoxLayout* login_icon_lay;
    QWidget* login_icon_widg;
    QLabel* login_topic_label;
    QHBoxLayout* login_topic_lay;
    QWidget* login_topic_widg;
    QLineEdit* login_id_text;
    QLineEdit* login_pass_text;
    QPushButton* login_button;
    QHBoxLayout* login_button_lay;
    QWidget* login_button_widg;
    QVBoxLayout* login_form_lay;
    QWidget* login_form_widg;
    //WHOLE FORM WIDGETS
    QHBoxLayout* whole_lay;
    QWidget* whole_widg;




};

#endif // ZPRAVA_H
