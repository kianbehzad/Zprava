#include "zpexperimental.h"

ZpExperimental::ZpExperimental(QWidget *parent) : QWidget(parent)
{
    //create your widget


    exp= new QVBoxLayout(this);
    ZpNavigationBar* nav = new ZpNavigationBar();
    exp->addWidget(nav);
    this->setLayout(exp);
}
