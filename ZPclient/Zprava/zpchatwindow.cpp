#include "zpchatwindow.h"

ZpChatWindow::ZpChatWindow(QWidget *parent) : QWidget(parent)
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
    splitter = new QSplitter(this);
    splitter->setChildrenCollapsible(false);
    splitter->addWidget(contactlist);
    splitter->addWidget(right_widg);
    navigationbar = new ZpNavigationBar(this);
    connect(navigationbar, SIGNAL(navigation_view(QString)), this, SLOT(user_info(QString)));
    whole_lay = new QVBoxLayout(this);
    whole_lay->setSpacing(0);
    whole_lay->setContentsMargins(0, 0, 0, 0);
    whole_lay->addWidget(navigationbar);
    whole_lay->addWidget(splitter);
    this->setLayout(whole_lay);
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

void ZpChatWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
    {
        contactlist->handle_clicked("~");
        prev_chatview->hide();
        right_lay->addWidget(chatview_holder, 0, 0, 14, 1);
        prev_chatview = chatview_holder;
        prev_chatview->show();
        prev_chattype->hide();
        right_lay->addWidget(chattype_holder, 14, 0, 1, 1);
        prev_chattype = chattype_holder;
        prev_chattype->show();
    }
}

void ZpChatWindow::add_new_contact(bool)
{
    contactlist->add_contact(userinfo->user->username);
    contactlist->handle_clicked(userinfo->user->username);
    handle_contact_clicked(userinfo->user->username);
}

void ZpChatWindow::user_info(QString username)
{
    userinfo = new ZpUserInfo(username);
    connect(userinfo->start_messaging_button, SIGNAL(clicked(bool)), this, SLOT(add_new_contact(bool)));
    prev_chatview->hide();
    prev_chattype->hide();
    right_lay->addWidget(userinfo, 0, 0, 14, 1);
    prev_chatview = userinfo;
    prev_chatview->show();
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
