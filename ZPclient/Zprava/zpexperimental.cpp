#include "zpexperimental.h"

ZpExperimental::ZpExperimental(QWidget *parent) : QWidget(parent)
{
    //create your widget


    exp= new QVBoxLayout(this);
    //exp->addWidget(::WIDGET::);
    this->setLayout(exp);
}
