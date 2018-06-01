#include "zpnavigationbar.h"

ZpNavigationBar::ZpNavigationBar(QWidget *parent) : QWidget(parent)
{

    //stylesheet
    apply_stylesheet();

    //widget
    create_form_navigation_widget();

}

void ZpNavigationBar::apply_stylesheet()
{
    //getting style sheets
    File.setFileName(":/navbar_stylesheet.qss");
    qDebug() << "is qt navbar_form_stylesheet opend: " <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();
}

void ZpNavigationBar::create_form_navigation_widget()
{
    //NAVIGATION BAR
    //left icon
    nav_icon_label = new QLabel();
    nav_icon_label->setObjectName("nav_logo_label");
    nav_icon_map = new QPixmap(":/Logo.png");
    nav_icon_label->setPixmap(*nav_icon_map);
    nav_icon_label->setMaximumSize(25, 25);
    nav_icon_lay = new QHBoxLayout();
    nav_icon_lay->addWidget(nav_icon_label);
    nav_icon_lay->setAlignment(nav_icon_label, Qt::AlignCenter);
    nav_icon_widg = new QWidget();
    nav_icon_widg->setLayout(nav_icon_lay);

    //status label
    nav_status_label = new QLabel();
    nav_status_label->setText("Test");
    nav_status_label->setObjectName("nav_status_label");
    nav_status_lay = new QHBoxLayout();
    nav_status_lay->addWidget(nav_status_label);
    //nav_status_lay->setAlignment(nav_status_label, Qt::AlignCenter);
    nav_status_widg = new QWidget();
    nav_status_widg->setLayout(nav_status_lay);

    //back button
    nav_back_button = new QPushButton();
    nav_back_button->setObjectName("nav_back_button");
    nav_back_button->setText("Back");
    nav_back_lay = new QHBoxLayout();
    nav_back_lay->addWidget(nav_back_button);
    nav_back_lay->setAlignment(nav_back_button, Qt::AlignCenter);
    nav_back_widg = new QWidget();
    nav_back_widg->setLayout(nav_back_lay);

    //whole navigation layout
    whole_lay = new QHBoxLayout();
    whole_lay->addWidget(nav_icon_label);
    whole_lay->setAlignment(nav_icon_label, Qt::AlignLeft);
    whole_lay->addWidget(nav_status_label);
    whole_lay->setAlignment(nav_status_label, Qt::AlignCenter);
    whole_lay->addWidget(nav_back_button);
    whole_lay->setAlignment(nav_back_button, Qt::AlignRight);
    if(this->layout() != nullptr)//TODO must delete all containig widgets
        delete this->layout();
    this->setLayout(whole_lay);
}

