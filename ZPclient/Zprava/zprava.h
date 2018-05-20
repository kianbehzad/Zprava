#ifndef ZPRAVA_H
#define ZPRAVA_H

#include <QMainWindow>
#include <QPushButton>

class Zprava : public QMainWindow
{
    Q_OBJECT

public:
    Zprava(QWidget *parent = 0);
    ~Zprava();
};

#endif // ZPRAVA_H
