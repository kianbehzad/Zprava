#ifndef ZPRAVA_H
#define ZPRAVA_H

#include <QMainWindow>
#include <QFile>
#include <QString>
#include "zpform.h"



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
    //FORM
    ZpForm* form;
public slots:
    void SLOTlogin_validate(QString username, QString password);




};

#endif // ZPRAVA_H
