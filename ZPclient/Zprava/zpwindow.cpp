#include "zpwindow.h"

ZpWindow::ZpWindow(QSplitter *parent)
{
    file.setFileName(qApp->applicationDirPath() + "/chats_data.json");

    contactlist = new ZpContactList();
    chatview = new QWidget(this);
    sender = new QWidget(this);
    right_lay = new QGridLayout(this);
    right_lay->addWidget(chatview, 0, 0, 14, 1);
    right_lay->addWidget(sender, 14, 0, 1, 1);
    right_lay->setSpacing(0);
    right_lay->setContentsMargins(0, 0, 0, 0);
    right_widg = new QWidget(this);
    right_widg->setLayout(right_lay);
    splitter = new QSplitter(Qt::Horizontal);
    this->addWidget(contactlist);
    this->addWidget(right_widg);
    sender->setStyleSheet("border: 3px solid black");//TODO: remove
    //chatview->setStyleSheet("border: 3px solid black");//TODO: remove
}

void ZpWindow::handle_threadUpdate()
{
    bool is_opened = file.open(QFile::ReadOnly);
    //qDebug() << "is chats_data: " << is_opened;
    if(is_opened)
        file_data = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(file_data.toUtf8());
    QJsonObject object = document.object();
    for(const auto& username: object.keys())
    {
        bool exists{false};
        //check if the contact already exists
        for(const auto& contact: contactlist->contacts_list)
            if(contact->user->username == username)
                exists = true;
        if(!exists)
        {
            contactlist->add_contact(username);
            connect(this, SIGNAL(thread_updateStep2()), contactlist->get_contact(username), SLOT(handle_threadUpdate()));
            QVBoxLayout* lay = new QVBoxLayout();
            lay->addWidget(contactlist->get_contact(username)->chatview);
            chatview->setLayout(lay);
        }
    }
    emit thread_updateStep2();
}
