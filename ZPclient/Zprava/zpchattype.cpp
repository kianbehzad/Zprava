#include "zpchattype.h"


ZpChatType::ZpChatType(ZpUser* _opponent,QWidget *parent) : QWidget(parent)
{
    opponent = _opponent;
    apply_stylesheet();
    type_height = 25;
    line_nums_before = 0;
    type_lay  = new QGridLayout();
    send_but = new ClickableLabel();
    failure_logo = new QLabel();
    failure_pic = new QPixmap(":/failure_logo.png");
    failure_logo->setPixmap(*failure_pic);
    failure_logo->setAlignment(Qt::AlignCenter);
    type = new QTextEdit();
    type->setFixedHeight(26);
    type->setObjectName("type_widg");
    type->setFrameStyle(QFrame::NoFrame);
    type_lay->addWidget(send_but,0,23,1,1,Qt::AlignBottom);
    type_lay->addWidget(type,0,1,1,22,Qt::AlignBottom);
    type_lay->addWidget(failure_logo,0,0,1,1,Qt::AlignBottom);
    failure_logo->hide();
    type_lay->setMargin(0);
    type_lay->setContentsMargins(0,0,0,0);
    type_lay->setSpacing(3);
    send_but->setObjectName("send_but");
    type_lay->setContentsMargins(0,0,0,0);
    type_lay->setVerticalSpacing(0);
    this->setLayout(type_lay);
    this->setMaximumHeight(27);
    this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    QPalette pal = palette();
    // set white background
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    shortcut = new QShortcut(QKeySequence(Qt::Key_Enter + Qt::Key_Q), this);

    connect(this,SIGNAL(increment_size()), this,SLOT(add_size()));
    connect(type,SIGNAL(textChanged()), this,SLOT(check_size()));
    connect(send_but,SIGNAL(clicked()),this,SLOT(but_callback()));
    connect(this,SIGNAL(decrement_size()),this,SLOT(minus_size()));
    //connect(shortcut,SIGNAL(activated()),this,SLOT(send()));
    //connect(send_but,SIGNAL(signalMouseHover(QLabel*)),this,SLOT(label_hover(QLabel*)));


}

void ZpChatType::add_size()
{
    type_height+=14;
    this->setFixedHeight(type_height);
    type->setFixedHeight(type_height);
}

void ZpChatType::minus_size()
{
    type_height-=14;
    this->setFixedHeight(type_height);
    type->setFixedHeight(type_height);
}

void ZpChatType::but_callback()
{
    QString s = type->toPlainText();
    initial_networking_navigationbar(s);
}

void ZpChatType::check_size()
{
    type->setFrameStyle(QFrame::Box);
    margins = type->contentsMargins();
    documentSize =  type->document()->documentLayout()->documentSize();
    height = documentSize.height() + margins.top() + margins.bottom() + 1;
    lines_num = (height - 29)/14;
    qDebug()<<lines_num;
    type->setFrameStyle(QFrame::NoFrame);
    if(lines_num - line_nums_before == 1)
    {
        line_nums_before = lines_num;
        emit increment_size();
    }
    else if(lines_num - line_nums_before == -1)
    {
        line_nums_before = lines_num;
        emit decrement_size();

    }
    else if(!(lines_num - line_nums_before == -1) && !(lines_num - line_nums_before == 1) && (lines_num == 0))
    {
        line_nums_before = lines_num;
        type_height = 25;
        type->setFixedHeight(25);
        this->setFixedHeight(25);
    }

}

void ZpChatType::apply_stylesheet()
{
    //getting style sheets
    File.setFileName(":/chat_stylesheet.qss");
    qDebug() << "is qt chat_stlesheet opend: " <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();

}

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent)
{
    send_logo = new QPixmap(":/send_logo9.png");
    this->setPixmap(*send_logo);
    this->setAlignment(Qt::AlignCenter);
}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}

bool ClickableLabel::event(QEvent *event)
{
    switch(event->type())
    {
    case QEvent::HoverEnter:
    hoverEnter(static_cast<QHoverEvent*>(event));
    return true;
    break;
    case QEvent::HoverLeave:
    hoverLeave(static_cast<QHoverEvent*>(event));
    return true;
    break;
    case QEvent::HoverMove:
    hoverMove(static_cast<QHoverEvent*>(event));
    return true;
    break;
    default:
    break;
    }
    return QWidget::event(event);
}

void ClickableLabel::hoverEnter(QHoverEvent *event)
{
    delete send_logo;
    send_logo = new QPixmap(":/send_logo8.png");
    this->setPixmap(*send_logo);
    this->setAlignment(Qt::AlignCenter);
}

void ClickableLabel::hoverLeave(QHoverEvent *event)
{
    delete send_logo;
    send_logo = new QPixmap(":/send_logo9.png");
    this->setPixmap(*send_logo);
    this->setAlignment(Qt::AlignCenter);
}

void ClickableLabel::hoverMove(QHoverEvent *event)
{
}

void ZpChatType::initial_networking_navigationbar(QString request)
{
    QString publisher = WHOAMI->username;
    QString subscriber = opponent->username;
    chat_network = new QNetworkAccessManager();
    chat_request = new QNetworkRequest();
    chat_request->setUrl(QUrl("http://127.0.0.1:8000/chat/newtextmessage/?publisher="+publisher+"&subscriber="+subscriber+"&textmessage="
                              +request));

    chat_reply = chat_network->get(*chat_request);
    connect(chat_reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(chat_reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(chat_reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));
}

void ZpChatType::slotReadyRead()
{

    type->clear();
    QString reply_string;
    std::vector<char> buf;
    qint64 chunk;

    QString allbuf;

    while(chat_reply->bytesAvailable() > 0) {
        chunk = chat_reply->bytesAvailable();
        if(chunk > 4096)
            chunk = 4096;

        buf.resize(chunk + 1);
        memset(& buf[0], 0, chunk + 1);

        if(chunk != chat_reply->read(& buf[0], chunk))
        {
            qDebug() <<"-> read error";//TODO: in QLabel
        }
        else
        {
            //qDebug() <<"-> read ok";//TODO: in QLabel
        }

        allbuf += & buf[0];
    }

    reply_string = allbuf;
    //qDebug() <<reply_string;//TODO remove this
    handle_reply(reply_string);
}

void ZpChatType::slotError(QNetworkReply::NetworkError err)
{
    //TODO: in QLabel
    qDebug() << "network error" << err;
    failure_logo->show();
    send_but->disconnect(send_but,SIGNAL(clicked()),this,SLOT(but_callback()));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(fade_failure()));
    timer->start(5000);
}

void ZpChatType::slotSslErrors(QList<QSslError> err)
{
    //TODO: in QLabel
    qDebug() << "unknown network error";

}

void ZpChatType::handle_reply(QString _reply)
{
}

void ZpChatType::fade_failure()
{
    timer->stop();
    failure_logo->hide();
    connect(send_but,SIGNAL(clicked()),this,SLOT(but_callback()));

}

void ZpChatType::keyReleaseEvent(QKeyEvent* e)
{
    if(e->modifiers() == Qt::Modifier::SHIFT && e->key() == Qt::Key_Escape)
    {
        emit send_but->clicked();
    }
}
QGridLayout* ZpChatType::get_layout()
{
    return type_lay;
}

