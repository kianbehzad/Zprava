#ifndef ZPNAVIGATIONBAR_H
#define ZPNAVIGATIONBAR_H

#include <QWidget>
#include<QDebug>
#include<QHBoxLayout>
#include<QPushButton>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QFont>
#include<QString>
#include<QWidget>
#include<QPixmap>
#include<Qlabel>
#include<QFile>
#include <QLatin1String>
#include<QGridLayout>
#include<QFontDatabase>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QUrl>
#include<QStringList>
#include<QCompleter>
#include<iostream>
#include<algorithm>
#include<sstream>

class ZpNavigationBar : public QWidget
{
    Q_OBJECT
public:
    explicit ZpNavigationBar(QWidget *parent = 0);
    void apply_stylesheet();

private:
    void initial_networking_navigationbar(QString);
    void handle_reply(QString _reply);

signals:

private:
    QGridLayout* navigation_bar_layout;
    QLineEdit* search_bar;
    QPushButton* search_but;
    QPushButton* setting_but;
    QPixmap* logo_bar;
    QLabel* icon_logo;
    QFile File;
    QString FormStyleSheet;
    QNetworkAccessManager* nav_network;
    QNetworkRequest* nav_request;
    QNetworkReply* nav_reply;
    QStringList suggested_words{};
    QCompleter* completer;
public slots:
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError err);
    void slotSslErrors(QList<QSslError> err);
    void slotTextChanged(QString);
    void slotSearchButClicked(bool);
    void slotSettingButClicked(bool);
};

#endif // ZPNAVIGATIONBAR_H
