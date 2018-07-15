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

    forward_descriptor = new QLabel();
    forward_descriptor->setObjectName("forward_descriptor");
    forward_descriptor->setText("Please Choose A User From Your Contacts");
    forward_descriptor->setAlignment(Qt::AlignCenter);
    //i dont know why but let the following be
    prev_chatview->hide();
    right_lay->addWidget(chatview_holder, 0, 0, 14, 1);
    prev_chatview = chatview_holder;
    prev_chatview->show();
    prev_chattype->hide();
    right_lay->addWidget(chattype_holder, 14, 0, 1, 1);
    prev_chattype = chattype_holder;
    prev_chattype->show();

    is_forward_proccess = false;
    connect(contactlist, SIGNAL(contact_clicked(QString)), this, SLOT(handle_contact_clicked(QString)));
    connect(contactlist, SIGNAL(message_menu_trig(QString,QString,QString)), this, SLOT(handle_message_menu_trig(QString,QString,QString)));
}

void ZpChatWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
    {
        is_forward_proccess = false;
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
    if(is_forward_proccess)
    {
        network = new QNetworkAccessManager();
        request = new QNetworkRequest();
        request->setUrl(QUrl(QString::fromStdString(IP_ADDRESS) + "chat/newtextmessage/?origin_publisher="+forwardinfo.origin_publisher+"&publisher="+WHOAMI->username+"&subscriber="+username+"&textmessage="+forwardinfo.message_data));
        reply = network->get(*request);
        is_forward_proccess = false;
    }
    prev_chatview->hide();
    right_lay->addWidget(contactlist->get_contact(username)->chatview, 0, 0, 14, 1);
    prev_chatview = contactlist->get_contact(username)->chatview;
    prev_chatview->show();
    prev_chattype->hide();
    right_lay->addWidget(contactlist->get_contact(username)->chattype, 14, 0, 1, 1);
    prev_chattype = contactlist->get_contact(username)->chattype;
    prev_chattype->show();
}

void ZpChatWindow::handle_message_menu_trig(QString which_content, QString origin_publisher, QString message_data)
{
    //qDebug() << which_content << origin_publisher << message_data;
    forwardinfo.which_content = which_content;
    forwardinfo.origin_publisher = origin_publisher;
    forwardinfo.message_data = message_data;
    prev_chatview->hide();
    prev_chattype->hide();
    right_lay->addWidget(forward_descriptor, 0, 0, 14, 1);
    prev_chatview = forward_descriptor;
    prev_chatview->show();
    is_forward_proccess = true;
}





