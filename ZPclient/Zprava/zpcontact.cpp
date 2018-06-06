#include "zpcontact.h"

ZpContact::ZpContact(QWidget *parent) : QWidget(parent)
{
    //getting style sheets
    File.setFileName(":/ZpContact_stylesheet.qss");
    qDebug() << "is qt ZpContact_stylesheet opend: " <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();

    //creating Zpcontact widget
    contact = new QLabel(this);
    contact->setObjectName("contact_label");
    icon = new QLabel(this);
    icon->setObjectName("icon_label");
    grid_lay = new QGridLayout(this);
    grid_lay->setSpacing(0);
    grid_lay->addWidget(contact, 0, 0, 1, 3);
    grid_lay->addWidget(icon, 0, 3, 1, 1);
    icon_map = new QPixmap();

}

void ZpContact::set_notification()
{
    if(!is_muted)
        icon_map->load(":/new_message_unmute.png");
    else
        icon_map->load(":/new_message_mute.png");
    icon->setAlignment(Qt::AlignCenter);
    icon->setPixmap(*icon_map);
}

void ZpContact::remove_notification()
{
    icon->clear();
}
