#include "zpmessage.h"

ZpMessage::ZpMessage(ZpUser* _opponent, bool _amIpublisher, int _pk, QWidget *parent) : QWidget(parent)
{
    opponent = _opponent;
    amIpublisher = _amIpublisher;
    pk = _pk;
    is_forward = false;

    context_menu = new QMenu(this);
    menu_forward = context_menu->addAction("forward");
    menu_forward = context_menu->addAction("delete");
    connect(context_menu, SIGNAL(triggered(QAction*)), this, SLOT(slot_menu_triggered(QAction*)));
}

void ZpMessage::mousePressEvent(QMouseEvent *event)
{
    switch (event->button())
    {
        case Qt::RightButton:
        {
            context_menu->exec(event->globalPos());
            break;
        }
        default:
            break;
    }
}

void ZpMessage::slotReadyRead()
{
    QString reply_string;
    std::vector<char> buf;
    qint64 chunk;

    QString allbuf;

    while(reply->bytesAvailable() > 0) {
        chunk = reply->bytesAvailable();
        if(chunk > 4096)
            chunk = 4096;

        buf.resize(chunk + 1);
        memset(& buf[0], 0, chunk + 1);

        if(chunk != reply->read(& buf[0], chunk))
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

void ZpMessage::slotError(QNetworkReply::NetworkError err)
{
    //TODO: in QLabel
    qDebug() << "network error" << err;
}

void ZpMessage::slotSslErrors(QList<QSslError> err)
{
    //TODO: in QLabel
    qDebug() << "unknown network error";

}
