#ifndef ZPCHATWINDOW_H
#define ZPCHATWINDOW_H
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QApplication>
#include <QFile>
#include <QString>
#include <QLatin1String>
#include <QDebug>
#include <QDir>
#include <QDebug>
#include <QDesktopWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAction>
#include <QTimer>
#include <QCheckBox>
#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QImageReader>

class zpchatwindow : public QWidget
{
    Q_OBJECT
public:
    explicit zpchatwindow(QWidget *parent = 0);

private:
void create_chatwindow();
void apply_stylesheet();

QFile File;
QString FormStyleSheet;
QHBoxLayout* chat_box_lay;
QTextEdit* chat_box;
QWidget* chat_box_widge;
QPixmap* back_chat;


QHBoxLayout* whole_chat_lay;





signals:

public slots:
};

#endif // ZPCHATWINDOW_H
