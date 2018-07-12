#include "zpchatwindow.h"

ZpChatWindow::ZpChatWindow(QWidget *parent) : QSplitter(parent)
{
    //getting style sheets
    File.setFileName(":/ZpChatWindow_stylesheet.qss");
    qDebug() << "is qt ZpChatWindow_stylesheet opend: " <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();

    //widget
    prev_chatview = new QWidget(this);
    prev_chattype = new QWidget(this);
    chatview_holder = new QWidget(this);
    chatview_holder->setMinimumWidth(700);
    chatview_holder->setContentsMargins(0, 0, 0, 0);

    chattype_holder = new QWidget(this);
    right_lay = new QGridLayout(this);
    right_lay->addWidget(chatview_holder, 0, 0, 14, 1);
    right_lay->addWidget(chattype_holder, 14, 0, 1, 1);
    right_lay->setSpacing(0);
    right_lay->setContentsMargins(0, 0, 0, 0);
    right_widg = new QWidget(this);
    right_widg->setContentsMargins(0, 0, 0, 0);
    right_widg->setLayout(right_lay);
    contactlist = new ZpContactList();
    this->addWidget(contactlist);
    this->addWidget(right_widg);
    //i dont know why but let the following be
    prev_chatview->hide();
    right_lay->addWidget(chatview_holder, 0, 0, 14, 1);
    prev_chatview = chatview_holder;
    prev_chatview->show();
    prev_chattype->hide();
    right_lay->addWidget(chattype_holder, 14, 0, 1, 1);
    prev_chattype = chattype_holder;
    prev_chattype->show();

    connect(contactlist, SIGNAL(contact_clicked(QString)), this, SLOT(handle_contact_clicked(QString)));
}

void ZpChatWindow::handle_contact_clicked(QString username)
{
    prev_chatview->hide();
    right_lay->addWidget(contactlist->get_contact(username)->chatview, 0, 0, 14, 1);
    prev_chatview = contactlist->get_contact(username)->chatview;
    prev_chatview->show();
    prev_chattype->hide();
    right_lay->addWidget(contactlist->get_contact(username)->chattype, 14, 0, 1, 1);
    prev_chattype = contactlist->get_contact(username)->chattype;
    prev_chattype->show();
}
