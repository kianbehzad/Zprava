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
#include<QEvent>
#include<QtEvents>
#include<QHoverEvent>
#include<QMouseEvent>
#include<QObject>
#include<QColor>
#include "zpglobals.h"


class NavigationLabel : public QLabel {
    Q_OBJECT

public:
    explicit NavigationLabel(QPixmap*, QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    void enterEvent(QEvent *ev) override
        {
        delete send_logo;
        send_logo = new QPixmap(":/setting_logo2.png");
        this->setPixmap(*send_logo);
        this->setAlignment(Qt::AlignCenter);
        }

    void leaveEvent(QEvent *ev) override
        {
        delete send_logo;
        send_logo = new QPixmap(":/setting_logo1.png");
        this->setPixmap(*send_logo);
        this->setAlignment(Qt::AlignCenter);
        }
    ~NavigationLabel();
signals:
    void clicked();

private:
    QPixmap* send_logo;
protected:
    void mousePressEvent(QMouseEvent* event);
};
class NavigationLabel2 : public QLabel {
    Q_OBJECT

public:
    explicit NavigationLabel2(QPixmap*, QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    void enterEvent(QEvent *ev) override
        {
        delete send_logo;
        send_logo = new QPixmap(":/search_logo2.png");
        this->setPixmap(*send_logo);
        this->setAlignment(Qt::AlignCenter);
        }

    void leaveEvent(QEvent *ev) override
        {
        delete send_logo;
        send_logo = new QPixmap(":/search_logo1.png");
        this->setPixmap(*send_logo);
        this->setAlignment(Qt::AlignCenter);
        }
    ~NavigationLabel2();
signals:
    void clicked();

private:
    QPixmap* send_logo;
protected:
    void mousePressEvent(QMouseEvent* event);
};

class ZpNavigationBar : public QWidget
{
    Q_OBJECT
public:
    explicit ZpNavigationBar(QWidget *parent = 0);
    void apply_stylesheet();
    NavigationLabel* setting_but;

private:
    void initial_networking_navigationbar(QString);
    void handle_reply(QString _reply);

signals:

private:
    QGridLayout* navigation_bar_layout;
    QLineEdit* search_bar;
    NavigationLabel2* search_but;
    QPixmap* search_logo1;
    QPixmap* search_logo2;
    QPixmap* setting_logo1;
    QPixmap* setting_logo2;
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
    void slotSearchButClicked();
    //void slotSettingButClicked();

signals:
    void navigation_view(QString username);
};

#endif // ZPNAVIGATIONBAR_H
