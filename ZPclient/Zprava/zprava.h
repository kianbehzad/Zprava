#ifndef ZPRAVA_H
#define ZPRAVA_H

#include <QMainWindow>
#include "zpform.h"



class Zprava : public QMainWindow
{
    Q_OBJECT

public:
    Zprava(QWidget *parent = 0);
    ~Zprava();
    //FORM
    ZpForm* form;





};

#endif // ZPRAVA_H
