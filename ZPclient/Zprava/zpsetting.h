#ifndef ZPSETTING_H
#define ZPSETTING_H

#include <QWidget>
#include<QLabel>
#include<QPixmap>
#include<QLineEdit>
#include<QPushButton>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QVBoxLayout>
#include<QComboBox>
#include <QImage>
#include<QFile>
#include<QString>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QList>
#include<QAction>
#include"zpuser.h"




class ZpSetting : public QWidget
{
    Q_OBJECT
public:
    explicit ZpSetting(ZpUser* ,QWidget *parent = 0);

    void apply_stylesheet();

    ZpUser* user;
    QVBoxLayout* whole_lay;

    QHBoxLayout* setting_lay;
    QHBoxLayout* pic_lay;
    QHBoxLayout* username_lay;
    QHBoxLayout* password_lay;
    QHBoxLayout* timezone_lay;
    QHBoxLayout* buts_lay;

    QWidget* setting_widg;
    QWidget* pic_widg;
    QWidget* username_widg;
    QWidget* password_widg;
    QWidget* timezone_widg;
    QWidget* buts_widg;

    QLabel* setting_label;
    QLabel* username_label;
    QLabel* password_label;
    QLabel* pic_label;
    QLabel* timezone_label;

    QPushButton* save_but;
    QPushButton* logout_but;

    QLineEdit* username_change;
    QLineEdit* password_change;

    QComboBox* timezone;

    QString FormStyleSheet;
    QString nusername;
    QString npassword;
    QString username;

    QFile File;

    QNetworkAccessManager* network;

    QNetworkRequest* request;

    QNetworkReply* reply;

    QList<QString>* request_list;
    QAction* username_exist;
    QAction*  empty_username_field;

    QLabel* username_label3;
    QLabel* password_label3;


    void initiate_networking(QList<QString>*);
    void handle_reply(QString _reply);

public slots:
    void send_info(bool);
    void logout(bool);
    void handle_timezone(QString);
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError err);
    void slotSslErrors(QList<QSslError> err);


signals:
    void signal_combobox(QString);

public slots:
};

#endif // ZPSETTING_H
