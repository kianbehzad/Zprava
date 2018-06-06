#include "zpcontact.h"

ZpContact::ZpContact(QWidget *parent) : QWidget(parent)
{
    //getting style sheets
    File.setFileName(":/ZpContact_stylesheet.qss");
    qDebug() << "is qt ZpContact_stylesheet opend: " <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();

    //creating Zpcontact widget
    contact = new QLabel(this);
    contact->setObjectName("contact_label");
    icon = new QLabel(this);
    icon->setObjectName("icon_label");
    grid_lay = new QGridLayout(this);
    grid_lay->setSpacing(0);
    grid_lay->addWidget(contact, 0, 0, 1, 3);
    grid_lay->addWidget(icon, 0, 3, 1, 1);
    icon_map = new QPixmap();

    //date and time
    datetime = new QDateTime();

}

void ZpContact::set_notification()
{
    if(!is_muted)
        icon_map->load(":/new_message_unmute.png");
    else
        icon_map->load(":/new_message_mute.png");
    icon->setAlignment(Qt::AlignCenter);
    icon->setPixmap(*icon_map);
}

void ZpContact::remove_notification()
{
    icon->clear();
}

void ZpContact::set_datetime(int year, int month, int day, int hour, int minute, int second)
{
    QDate date_temp{};
    date_temp.setDate(year, month, day);
    QTime time_temp{};
    if(!date_temp.isValid() || !time_temp.setHMS(hour, minute, second))
    {
        qDebug() << "wrong datetime entry please check again";
        return;
    }
    datetime->setDate(QDate(year, month, day));
    datetime->setTime(QTime(hour, minute, second));
}

bool ZpContact::operator<(const ZpContact &op) const
{
    return (datetime->operator <(*op.datetime));
}

bool ZpContact::operator ==(const ZpContact &op) const
{
    return (datetime->operator ==(*op.datetime));
}

void ZpContact::mousePressEvent(QMouseEvent *event)
{
    emit clicked(contact->text());
}

