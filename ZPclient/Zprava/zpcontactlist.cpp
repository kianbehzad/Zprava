#include "zpcontactlist.h"

ZpContactList::ZpContactList(QScrollArea *parent) : QScrollArea(parent)
{
    //layout
    contacts_list_layout = new QVBoxLayout(this);
    contacts_list_layout->setContentsMargins(0, 0, 0, 0);
    contacts_list_layout->setSpacing(0);

    //widget
    contact_list_widget = new QWidget(this);
    contact_list_widget->setLayout(contacts_list_layout);
    contact_list_widget->setContentsMargins(0, 0, 0, 0);

    //scroll bar
    this->setWidget(contact_list_widget);
    this->setAlignment(Qt::AlignCenter);
    this->setWidgetResizable(true);
    this->setMinimumWidth(100);

}

void ZpContactList::add_contact(QString username)
{
    ZpContact* new_contact = new ZpContact(username, this);
    new_contact->setMinimumHeight(50);
    contacts_list_layout->addWidget(new_contact);
    contacts_list.push_back(new_contact);
}
