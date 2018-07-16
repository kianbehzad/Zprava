#ifndef ZPRAVA_H
#define ZPRAVA_H

#include <QMainWindow>
#include <QFile>
#include <QLabel>
#include <QString>
#include "zpexperimental.h"
#include "zpform.h"
#include "zpuser.h"
#include "zpthread.h"
#include "zpchatwindow.h"
#include "zpglobals.h"



class Zprava : public QMainWindow
{
    Q_OBJECT

public:
    Zprava(QWidget *parent = 0);
    ~Zprava();
    //stylesheet
    void apply_stylesheet();
    QFile File;
    QString FormStyleSheet;
    //experimental
    ZpExperimental* experiment;
    //FORM
    ZpForm* form;
    //not connected
    QLabel* connection;

    //LOGIN
    ZpThread* thread;
    ZpChatWindow* chatwindow;

public slots:
    void login(QString username,QString password);
    void handle_is_connected(bool is_connected);

};

#endif // ZPRAVA_H
