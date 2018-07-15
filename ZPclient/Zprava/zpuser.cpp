#include "zpuser.h"

ZpUser::ZpUser(QString _username, QObject *parent) : QObject(parent)
{
    username = _username;
    last_message_datetime = QDateTime::currentDateTime();
    email = "unknown";

    //network
    network = new QNetworkAccessManager();
    request = new QNetworkRequest();
    request->setUrl(QUrl("http://zprava.ir/navigation/userdata/?username=" + _username));
    reply = network->get(*request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));
}

void ZpUser::handle_reply(QString _reply)//TODO for just returning states
{
    if(_reply == "InvalidUserName")
    {
        qWarning() << "ZpUser -> invalid username";
        username = "Invalid Username";
        email = "Unknown!";
        last_message_datetime = QDateTime::currentDateTime();
    }
    else
    {
        QJsonDocument document = QJsonDocument::fromJson(_reply.toUtf8());
        QJsonObject object = document.object();
        username = object["username"].toString();
        email = object["email"].toString();
        if(!QDateTime::fromString(object["last_message_datetime"].toString(), Qt::ISODate).isValid())
        {
            qWarning() << "ZpUser -> invalid datetime";
            last_message_datetime = QDateTime::currentDateTime();
        }
        else
        {
            last_message_datetime = QDateTime::fromString(object["last_message_datetime"].toString(), Qt::ISODate);
        }
    }
    emit updated();
}


void ZpUser::slotReadyRead()
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

void ZpUser::slotError(QNetworkReply::NetworkError err)
{
    //TODO: in QLabel
    qDebug() << "network error" << err;
}

void ZpUser::slotSslErrors(QList<QSslError> err)
{
    //TODO: in QLabel
    qDebug() << "unknown network error";

}


