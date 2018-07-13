#include "zpnavigationbar.h"

ZpNavigationBar::ZpNavigationBar(QWidget *parent) : QWidget(parent)
{


    // Stylesheet
    apply_stylesheet();

    // Setting up some Fonts to use in Widget
    QFontDatabase::addApplicationFont(":/DancingScript-Regular.otf");
    QFont font_logo = QFont("Dancing Script OT",17);
    QFontDatabase::addApplicationFont(":/Quicksand-Regular.otf");
    QFont font_button = QFont("QuickSand",15);

    // GUI build-up
    navigation_bar_layout= new QGridLayout();
    search_bar = new QLineEdit();
    icon_logo = new QLabel();
    icon_logo->setObjectName("icon_logo");
    search_bar->setObjectName("search_bar");
    search_logo1 = new QPixmap(":/search_logo1.png");
    search_logo2 = new QPixmap(":/search_logo2.png");
    setting_logo1 = new QPixmap(":/setting_logo1.png");
    setting_logo2 = new QPixmap(":/setting_logo2.png");
    search_but = new NavigationLabel2(search_logo1);
    setting_but = new NavigationLabel(setting_logo1);

    icon_logo->setText("ZPrava");
    icon_logo->setFont(font_logo);

    navigation_bar_layout->addWidget(icon_logo,0,0,1,1, Qt::AlignTop);
    navigation_bar_layout->addWidget(search_bar,0,1,1,10,Qt::AlignTop);
    navigation_bar_layout->addWidget(search_but,0,11,1,1,Qt::AlignTop);
    navigation_bar_layout->addWidget(setting_but,0,12,1,1,Qt::AlignTop);
    this->setLayout(navigation_bar_layout);

    QColor* color = new QColor(155,151,156);
    QPalette pal = palette();
    // set white background
    pal.setColor(QPalette::Background, *color);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->setFixedHeight(50);
    completer = new QCompleter(suggested_words, this);


    connect(search_bar,SIGNAL(textEdited(QString)), this,SLOT(slotTextChanged(QString)));
    connect(search_but,SIGNAL(clicked()),this,SLOT(slotSearchButClicked()));
    connect(setting_but,SIGNAL(clicked()),this,SLOT(slotSettingButClicked()));


}

void ZpNavigationBar::apply_stylesheet()
{
    //getting style sheets
    File.setFileName(":/nav_stylesheet.qss");
    qDebug() << "is qt nav_stylesheet opend: " <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();
}

void ZpNavigationBar::initial_networking_navigationbar(QString request)
{
    nav_network = new QNetworkAccessManager();
    nav_request = new QNetworkRequest();
    nav_request->setUrl(QUrl("http://127.0.0.1:8000/navigation/search/?word="+request));

    nav_reply = nav_network->get(*nav_request);
    connect(nav_reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(nav_reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(nav_reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));
}
void ZpNavigationBar::slotReadyRead()
{
    QString reply_string;
    std::vector<char> buf;
    qint64 chunk;

    QString allbuf;

    while(nav_reply->bytesAvailable() > 0) {
        chunk = nav_reply->bytesAvailable();
        if(chunk > 4096)
            chunk = 4096;

        buf.resize(chunk + 1);
        memset(& buf[0], 0, chunk + 1);

        if(chunk != nav_reply->read(& buf[0], chunk))
        {
            qDebug() <<"-> read error";//TODO: in QLabel
        }
        else
        {
            qDebug() <<"-> read ok";//TODO: in QLabel
        }

        allbuf += & buf[0];
    }

    reply_string = allbuf;
    //qDebug() <<reply_string;//TODO remove this
    handle_reply(reply_string);
}
void ZpNavigationBar::slotError(QNetworkReply::NetworkError err)
{
    //TODO: in QLabel
    qDebug() << "network error" << err;
}

void ZpNavigationBar::slotSslErrors(QList<QSslError> err)
{
    //TODO: in QLabel
    qDebug() << "unknown network error";

}
void ZpNavigationBar::handle_reply(QString _reply)
{
    suggested_words.clear();
    std::string std_string_reply = _reply.toStdString();
    std::stringstream ss(std_string_reply);
    std::string token{};
    QString tdelimiter{};
    QString last{};
    char delim = '~';
    while (std::getline(ss, token, delim))
    {
        tdelimiter = QString::fromStdString(token);
        suggested_words.append(tdelimiter);
    }
    suggested_words[0].remove("\"");
    suggested_words.last().remove("\"");

    // Auto-complete handling
    delete completer;
    completer = new QCompleter(suggested_words, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    search_bar->setCompleter(completer);
    search_bar->completer()->complete();


}

void ZpNavigationBar::slotTextChanged(QString s)
{
    initial_networking_navigationbar(s);
}

void ZpNavigationBar::slotSearchButClicked()
{
    emit navigation_view(search_bar->text());
}

void ZpNavigationBar::slotSettingButClicked()
{
    qDebug()<<"setting";
}

NavigationLabel::NavigationLabel(QPixmap* pic, QWidget* parent, Qt::WindowFlags f)
: QLabel(parent)
{
send_logo = new QPixmap(*pic);

this->setPixmap(*send_logo);
this->setAlignment(Qt::AlignCenter);
}

NavigationLabel::~NavigationLabel() {}

void NavigationLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}

NavigationLabel2::NavigationLabel2(QPixmap* pic, QWidget* parent, Qt::WindowFlags f)
: QLabel(parent)
{
send_logo = new QPixmap(*pic);

this->setPixmap(*send_logo);
this->setAlignment(Qt::AlignCenter);
}

NavigationLabel2::~NavigationLabel2() {}

void NavigationLabel2::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
}





