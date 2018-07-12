#include "zpcontact.h"

ZpContact::ZpContact(QString username, QWidget *parent) : QWidget(parent)
{
    user = new ZpUser(username);
    connect(user, SIGNAL(updated()), this, SLOT(handle_update()));
    chatview = new ZpChatView(user);
    connect(this, SIGNAL(trig_ZpChatview()), chatview, SLOT(updating()));
    chattype = new ZpChatType(user, this);

    //getting style sheets
    File.setFileName(":/ZpContact_stylesheet.qss");
    qDebug() << "is qt ZpContact_stylesheet opend: " <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();

    this->setFixedHeight(Height);
    //creating Zpcontact widget
    grid = new QGridLayout(this);
    grid->setContentsMargins(0, 0, 0,0);
    grid->setSpacing(0);
    picture = new QLabel(this);
    picture->setObjectName("picture_label");
    title = new QLabel(this);
    title->setObjectName("title_label");
    notification = new QLabel(this);
    notification->setObjectName("notification_label");
    notification_map = new QPixmap();
    datetime = new QLabel(this);
    datetime->setObjectName("datetime_label");
    grid->addWidget(picture, 0, 0, 3, 1);
    grid->addWidget(title, 0, 1, 3, 2);
    grid->addWidget(notification, 0, 3, 2, 1);
    grid->addWidget(datetime, 2, 3, 1, 1);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setSpacing(0);
    grid->setMargin(0);
    this->setLayout(grid);
    this->setContentsMargins(0, 0, 0, 0);
    //context menu
    context_menu = new QMenu(this);
    menu_set_muted = context_menu->addAction("mute");
    menu_set_unmuted = context_menu->addAction("unmute");
    connect(context_menu, SIGNAL(triggered(QAction*)), this, SLOT(slot_menu_triggered(QAction*)));

}

void ZpContact::set_notification()
{
    if(!is_muted)
    {
        notification_map->load(":/notification_unmute.png");
    }
    else
    {
        notification_map->load(":/notification_mute.png");
    }
    notification->setAlignment(Qt::AlignRight);
    notification->setPixmap(*notification_map);
    has_notification = true;
}

void ZpContact::remove_notification()
{
    notification->clear();
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

void ZpContact::set_focused(bool isFocused)
{
    title->setProperty("clicked", isFocused);
    title->style()->unpolish(title);
    title->style()->polish(title);
    title->update();

    picture->setProperty("clicked", isFocused);
    picture->style()->unpolish(picture);
    picture->style()->polish(picture);
    picture->update();

    notification->setProperty("clicked", isFocused);
    notification->style()->unpolish(notification);
    notification->style()->polish(notification);
    notification->update();

    datetime->setProperty("clicked", isFocused);
    datetime->style()->unpolish(datetime);
    datetime->style()->polish(datetime);
    datetime->update();
}


void ZpContact::slot_menu_triggered(QAction * menu_action)
{
    if(menu_action->text() == "mute")
        this->set_muted();
    if(menu_action->text() == "unmute")
        this->set_unmuted();
}

void ZpContact::handle_update()
{
    QImage img(":/login.png");
    QImage img2 = img.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //picture->setScaledContents(true);//oh for god sake remove this
    picture->setAlignment(Qt::AlignCenter);
    picture->setPixmap(QPixmap::fromImage(img2));
    title->setText(user->username);
    title->setAlignment(Qt::AlignCenter);
    datetime->setText(user->last_message_datetime.time().toString("hh:mm"));
    datetime->setAlignment(Qt::AlignCenter);
}

void ZpContact::updating()
{
    emit trig_ZpChatview();
}

void ZpContact::mousePressEvent(QMouseEvent *event)
{
    switch (event->button())
    {
        case Qt::LeftButton:
        {
            emit clicked(title->text());
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

void ZpContact::enterEvent(QEvent *event)
{
    title->setProperty("hovered", true);
    title->style()->unpolish(title);
    title->style()->polish(title);
    title->update();

    picture->setProperty("hovered", true);
    picture->style()->unpolish(picture);
    picture->style()->polish(picture);
    picture->update();

    notification->setProperty("hovered", true);
    notification->style()->unpolish(notification);
    notification->style()->polish(notification);
    notification->update();

    datetime->setProperty("hovered", true);
    datetime->style()->unpolish(datetime);
    datetime->style()->polish(datetime);
    datetime->update();
}

void ZpContact::leaveEvent(QEvent *event)
{
    title->setProperty("hovered", false);
    title->style()->unpolish(title);
    title->style()->polish(title);
    title->update();

    picture->setProperty("hovered", false);
    picture->style()->unpolish(picture);
    picture->style()->polish(picture);
    picture->update();

    notification->setProperty("hovered", false);
    notification->style()->unpolish(notification);
    notification->style()->polish(notification);
    notification->update();

    datetime->setProperty("hovered", false);
    datetime->style()->unpolish(datetime);
    datetime->style()->polish(datetime);
    datetime->update();
}

