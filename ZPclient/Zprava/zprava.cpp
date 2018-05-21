#include "zprava.h"




Zprava::Zprava(QWidget *parent)
    : QMainWindow(parent)
{
    //set the form
    form = new ZpForm();
    setCentralWidget(form);
    centralWidget()->setFixedSize(800, 480);



}

Zprava::~Zprava()
{

}
