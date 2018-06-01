#include "zpchatwindow.h"

zpchatwindow::zpchatwindow(QWidget *parent) : QWidget(parent)
{
    create_chatwindow();

    apply_stylesheet();

}

void zpchatwindow::create_chatwindow()
{
    // chat box
    chat_box = new QTextEdit();
    chat_box_lay = new QHBoxLayout();
    chat_box_widge = new QWidget();
    chat_box->setObjectName("chat_box");
    chat_box->setPlaceholderText("Enter Message");
    chat_box_lay->heightForWidth(3);
    chat_box_lay->addWidget(chat_box);
    chat_box_widge->setLayout(chat_box_lay);

    back_chat = new QPixmap(":/building.png");


    //contacts


    // whole_chat
    whole_chat_lay = new QHBoxLayout();

    whole_chat_lay->addWidget(chat_box_widge);

    this->setLayout(whole_chat_lay);

}

void zpchatwindow::apply_stylesheet()
{
    //getting style sheets
    File.setFileName(":/chat_stylesheet.qss");
    qDebug() << "is qt form_stylesheet opend: " <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(FormStyleSheet);

}



