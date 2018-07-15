#include "zpthread.h"

ZpThread::ZpThread()
{
    file.setFileName(qApp->applicationDirPath() + "/chats_data.json");
}

void ZpThread::run()
{
    timer = new QTimer();
    timer->start(500);
    timer->moveToThread(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(handle_timer()));
    exec();

}

void ZpThread::handle_reply(QString reply_string)
{
    if(reply_string == "InvalidUserName") return;
    if(reply_string == "EmptyMessages") return;
    if(reply_string == "NoNewMessages") return;
    //else
    bool is_opened = file.open(QFile::WriteOnly);
    //qDebug() << "is chats_data: " << is_opened;
    if(is_opened)
    {
        QTextStream data{&file};
        data << reply_string;
    }
    file.close();
    emit updated();
}

void ZpThread::handle_timer()
{
    network = new QNetworkAccessManager();
    request = new QNetworkRequest();
    //if(getallchats)
        request->setUrl(QUrl("http://zprava.ir/chat/chatheaders/?username=" + WHOAMI->username));
    //else
    //    request->setUrl(QUrl("http://zprava.ir/chat/getnewchats/?username=" + username));
    reply = network->get(*request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));
}

void ZpThread::slotReadyRead()
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

void ZpThread::slotError(QNetworkReply::NetworkError err)
{
    //TODO: in QLabel
    qDebug() << "network error" << err;
}

void ZpThread::slotSslErrors(QList<QSslError> err)
{
    //TODO: in QLabel
    qDebug() << "unknown network error";

}
