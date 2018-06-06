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
    grid_lay->setContentsMargins(0, 0, 0,0);
    grid_lay->setSpacing(0);
    grid_lay->addWidget(contact, 0, 0, 1, 3);
    grid_lay->addWidget(icon, 0, 3, 1, 1);
    icon_map = new QPixmap();

    //date and time
    datetime = new QDateTime();

    //context menu
    context_menu = new QMenu(this);
    menu_set_muted = context_menu->addAction("mute");
    menu_set_unmuted = context_menu->addAction("unmute");
    connect(context_menu, SIGNAL(triggered(QAction*)), this, SLOT(slot_menu_triggered(QAction*)));

}

void ZpContact::set_notification()
{
    if(!is_muted)
        icon_map->load(":/new_message_unmute.png");
    else
        icon_map->load(":/new_message_mute.png");
    icon->setAlignment(Qt::AlignCenter);
    icon->setPixmap(*icon_map);
    has_notification = true;
}

void ZpContact::remove_notification()
{
    icon->clear();
    has_notification = false;
}

void ZpContact::set_muted()
{
    is_muted = true;
    if(has_notification)
        set_notification();
}

void ZpContact::set_unmuted()
{
    is_muted = false;
    if(has_notification)
        set_notification();
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

void ZpContact::slot_menu_triggered(QAction * menu_action)
{
    if(menu_action->text() == "mute")
        this->set_muted();
    if(menu_action->text() == "unmute")
        this->set_unmuted();
}

void ZpContact::mousePressEvent(QMouseEvent *event)
{
    switch (event->button())
    {
        case Qt::LeftButton:
        {
            emit clicked(contact->text());
            break;
        }
        case Qt::RightButton:
        {
            context_menu->exec(event->globalPos());
            break;
        }
        default:
            break;
    }
}

