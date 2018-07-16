#ifndef ZPSETTINGS_H
#define ZPSETTINGS_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QFile>
#include <QRect>
#include <QStyle>
#include <QLineEdit>
#include <QKeyEvent>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
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

    //change username widget
    QLabel* username_title;
    QLineEdit* username_editor;
    QPushButton* username_submit;
    QGridLayout* username_info_lay;
    QWidget* username_info_widg;
    QVBoxLayout* change_username_lay;
    QWidget* change_username_widg;
    QAction* wrong_username_input_action;

    //change password widget
    QLabel* old_password_title;
    QLineEdit* old_password_editor;
    QLabel* new_password_title;
    QLineEdit* new_password_editor;
    QPushButton* password_submit;
    QGridLayout* old_password_info_lay;
    QGridLayout* new_password_info_lay;
    QWidget* old_password_info_widg;
    QWidget* new_password_info_widg;
    QVBoxLayout* password_info_lay;
    QWidget* password_info_widg;
    QVBoxLayout* change_password_lay;
    QWidget* change_password_widg;
    QAction* wrong_old_password_input_action;
    QAction* wrong_new_password_input_action;

    //
    void resizeEvent(QResizeEvent*) override;
    QNetworkAccessManager* network;
    QNetworkRequest* request;
    QNetworkReply* reply;
    void handle_reply(QString _reply);
    enum class STATE
    {
        NONE = 0,
        USERNAME = 1,
        PASSWORD = 2,
    };
    STATE state = ZpSettings::STATE::NONE;




signals:

private slots:
    void handle_change_username_button(bool);
    void handle_change_password_button(bool);
    void handle_send_username(bool);
    void handle_send_password(bool);
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError err);
    void slotSslErrors(QList<QSslError> err);

};

#endif // ZPSETTINGS_H
