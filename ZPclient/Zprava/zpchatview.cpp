#include "zpchatview.h"

ZpChatView::ZpChatView(ZpUser *_opponent, QScrollArea *parent)
{
    this->opponent = _opponent;
    //layout
    messages_list_layout = new QVBoxLayout(this);
    messages_list_layout->setContentsMargins(0, 0, 0, 0);
    messages_list_layout->setSpacing(10);
    messages_list_layout->setMargin(0);
    filler = new QWidget(this);
    messages_list_layout->addWidget(filler);

    //widget
    messages_list_widget = new QWidget(this);
    messages_list_widget->setObjectName("chatview");
    messages_list_widget->setLayout(messages_list_layout);
    messages_list_widget->setContentsMargins(10, 10, 10, 10);

    //scroll bar
    messages_list_widget->setStyleSheet("QWidget#chatview{background-image:url(\":/chatview_backgroun.jpg\"); background-position: center;}");
//    QPixmap* bkgnd = new QPixmap(":/chatview_backgroun.jpg");
//    //*bkgnd = bkgnd->scaled(messages_list_widget->size(), Qt::IgnoreAspectRatio);
//    QPalette* palette = new QPalette();
//    palette->setBrush(QPalette::Background, *bkgnd);
//    messages_list_widget->setPalette(*palette);
    this->setWidget(messages_list_widget);
    this->setAlignment(Qt::AlignCenter);
    this->setWidgetResizable(true);
    this->setMinimumWidth(700);
    this->setContentsMargins(0, 0, 0, 0);

    data_thread = new ZpChatView_Thread(_opponent->username);
    connect(data_thread, SIGNAL(gotData(QList<MessageHeaders>)), this, SLOT(handle_gotData(QList<MessageHeaders>)));
}

void ZpChatView::add_message(ZpUser* _opponent, bool _amIpublisher, int _pk, ZpMessage::Type type)
{
    //check if the message already exists
    for(int i{}; i < message_list.size(); i++)
        if(message_list[i]->pk == _pk)
            return;
    ZpMessage* msg;
    if(type == ZpMessage::Type::TEXT)
    {
        ZpTextMessage* new_message = new ZpTextMessage(_opponent, _amIpublisher, _pk);
        msg = new_message;
    }
    connect(msg, SIGNAL(updated()), this, SLOT(handle_update()));
    message_list.push_back(msg);
}

ZpMessage *ZpChatView::get_message(int pk)
{
    for(const auto& msg: message_list)
        if(msg->pk == pk)
            return msg;
    //nothing found(if this line reached means something in code is wrong)
    return nullptr;
}

void ZpChatView::sort()
{
    for(const auto& msg : message_list)
        messages_list_layout->removeWidget(msg);
    messages_list_layout->removeWidget(filler);
    std::sort(message_list.begin(), message_list.end(), [](ZpMessage* a, ZpMessage* b){return (a->datetime < b->datetime);});
    //update GUI
    for(const auto& msg : message_list)
    {
        if(msg->amIpublisher)
            messages_list_layout->addWidget(msg, 0, Qt::AlignRight);
        else
            messages_list_layout->addWidget(msg, 0, Qt::AlignLeft);
    }
    int filler_height{};
    for(const auto& msg: message_list)
        filler_height += msg->widget_height;
    if(this->height() - filler_height > 0)
    {
        filler->setFixedHeight(this->height() - filler_height);
        messages_list_layout->addWidget(filler);
    }
}

QWidget *ZpChatView::get_widget()
{
    return messages_list_widget;
}

void ZpChatView::handle_update()
{
    this->sort();
}

void ZpChatView::handle_gotData(QList<MessageHeaders> messageheaders)
{
    for(const auto& header: messageheaders)
        this->add_message(opponent, header.amIPub, header.pk, header.type);
    this->sort();
}

void ZpChatView::updating()
{
    data_thread->start();
}

void ZpChatView::resizeEvent(QResizeEvent *)
{
    this->sort();
}










