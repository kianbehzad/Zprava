#include "zpcontactlist.h"

ZpContactList::ZpContactList(QScrollArea *parent) : QScrollArea(parent)
{
    //layout
    contacts_list_layout = new QVBoxLayout(this);
    contacts_list_layout->setContentsMargins(0, 0, 0, 0);
    contacts_list_layout->setSpacing(0);
    contacts_list_layout->setMargin(0);
    filler = new QWidget(this);
    contacts_list_layout->addWidget(filler);

    //widget
    contact_list_widget = new QWidget(this);
    contact_list_widget->setObjectName("contactlist");
    contact_list_widget->setLayout(contacts_list_layout);
    contact_list_widget->setContentsMargins(0, 0, 0, 0);
    contact_list_widget->setStyleSheet("QWidget#contactlist{background-color: white;}");

    //scroll bar
    this->setWidget(contact_list_widget);
    this->setAlignment(Qt::AlignCenter);
    this->setWidgetResizable(true);
    this->setMinimumWidth(300);
    this->setContentsMargins(0, 0, 0, 0);

    data_thread = new ZpContactList_Thread();
    connect(data_thread, SIGNAL(gotData(QList<QString>,QList<QString>)), this, SLOT(handle_gotData(QList<QString>,QList<QString>)));

}

void ZpContactList::add_contact(QString username)
{
    //check if the username already exists
    for(int i{}; i < contacts_list.size(); i++)
        if(contacts_list[i]->user->username == username)
            return;
    ZpContact* new_contact = new ZpContact(username, this);
    connect(new_contact->chatview, SIGNAL(message_menu_trig(QString,QString,QString)), this, SLOT(handle_message_menu_trig(QString,QString,QString)));
    connect(this, SIGNAL(trig_ZpContact()), new_contact, SLOT(updating()));
    connect(new_contact->user, SIGNAL(updated()), this, SLOT(handle_update()));
    connect(new_contact, SIGNAL(clicked(QString)), this, SLOT(handle_clicked(QString)));
    contacts_list_layout->addWidget(new_contact, 0, Qt::AlignTop);
    contacts_list.push_back(new_contact);
    contacts_list_layout->removeWidget(filler);
    filler->setFixedHeight(this->height() - contacts_list.size()*ZpContact::Height);
    contacts_list_layout->addWidget(filler);
}

ZpContact* ZpContactList::get_contact(QString username)
{
    for(int i{}; i < contacts_list.size(); i++)
        if(contacts_list[i]->user->username == username)
            return contacts_list[i];
    //nothing found(if this line reached means something in code is wrong)
    return nullptr;
}

void ZpContactList::sort()
{
    for(const auto& contact : contacts_list)
        contacts_list_layout->removeWidget(contact);
    contacts_list_layout->removeWidget(filler);
    std::sort(contacts_list.begin(), contacts_list.end(), [](ZpContact* a, ZpContact* b){return (a->user->last_message_datetime > b->user->last_message_datetime);});
    //update GUI
    for(const auto& contact : contacts_list)
        contacts_list_layout->addWidget(contact, 0, Qt::AlignTop);
    if(this->height() - contacts_list.size()*ZpContact::Height > 0)
        filler->setFixedHeight(this->height() - contacts_list.size()*ZpContact::Height);
    else
        filler->setFixedHeight(0);
    contacts_list_layout->addWidget(filler);
}

void ZpContactList::handle_update()
{
    this->sort();
}

void ZpContactList::handle_gotData(QList<QString> username, QList<QString> deleted)
{
    for(const auto& contact: username)
        this->add_contact(contact);
    for(const auto& del: deleted)
    {
        ZpContact* tmp = get_contact(del);
        contacts_list_layout->removeWidget(tmp);
        tmp->hide();
        for(int i{}; i < contacts_list.size(); i++)
            if(contacts_list[i]->user->username == del)
                contacts_list.removeAt(i);
    }
}

void ZpContactList::updating()
{
    data_thread->start();
    emit trig_ZpContact();
}

void ZpContactList::resizeEvent(QResizeEvent *)
{
    this->sort();
}

void ZpContactList::handle_clicked(QString username)
{
    for(const auto& contact : contacts_list)
        contact->set_focused(false);
    if(username == "~")
        return;
    get_contact(username)->set_focused(true);
    emit contact_clicked(username);
}

void ZpContactList::handle_message_menu_trig(QString which_content, QString publisher, QString message_data)
{
    emit message_menu_trig(which_content, publisher, message_data);
}
