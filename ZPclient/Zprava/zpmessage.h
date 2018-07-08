#ifndef ZPMESSAGE_H
#define ZPMESSAGE_H

#include <QDateTime>
#include <QString>
#include <QWidget>
#include "zpuser.h"

class ZpMessage
{
public:
    enum class Type
    {
        TEXT = 0,
        PHOTO = 1,
        AUDIO = 2,
        VIDEO = 3
    };
    ZpMessage(ZpUser* _opponent, bool _amIpublisher, QString _datetime, bool _is_seen, Type _type, int _pk);
    void set_data(ZpUser* _opponent, bool _amIpublisher, QString _datetime, bool _is_seen, Type _type, int _pk);
    virtual QWidget* widget() = 0;
    ZpUser* opponent;
    bool amIpublisher;
    QDateTime datetime;
    bool is_seen;
    Type type;
    int pk;

};

#endif // ZPMESSAGE_H
