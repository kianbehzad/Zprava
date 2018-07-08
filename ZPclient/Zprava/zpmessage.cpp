#include "zpmessage.h"

ZpMessage::ZpMessage(ZpUser* _opponent, bool _amIpublisher, QString _datetime, bool _is_seen, Type _type, int _pk)
{
    opponent = _opponent;
    amIpublisher = _amIpublisher;
    if(QDateTime::fromString(_datetime, Qt::ISODate).isValid())
        datetime = QDateTime::fromString(_datetime, Qt::ISODate);
    else
        datetime = QDateTime::currentDateTime();
    is_seen = _is_seen;
    type = _type;
    pk = _pk;
}

void ZpMessage::set_data(ZpUser *_opponent, bool _amIpublisher, QString _datetime, bool _is_seen, ZpMessage::Type _type, int _pk)
{
    opponent = _opponent;
    amIpublisher = _amIpublisher;
    if(QDateTime::fromString(_datetime, Qt::ISODate).isValid())
        datetime = QDateTime::fromString(_datetime, Qt::ISODate);
    else
        datetime = QDateTime::currentDateTime();
    is_seen = _is_seen;
    type = _type;
    pk = _pk;
}
