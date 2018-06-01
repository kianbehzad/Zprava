#ifndef ZPRAVA_H
#define ZPRAVA_H

#include <QMainWindow>
#include <QFile>
#include <QString>
#include <QDockWidget>
#include "zpform.h"
#include "zpnavigationbar.h"



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
    //NAVBAR
    ZpNavigationBar* navbar_widg;
    QDockWidget* navbar_dock;





};

#endif // ZPRAVA_H
