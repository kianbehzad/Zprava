#ifndef ZPFORM_H
#define ZPFORM_H

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

class ZpForm : public QWidget
{
    Q_OBJECT
public:
    explicit ZpForm(QWidget *parent = 0);
private:
    enum class STATE
    {
        NONE = 0,
        LOGIN = 1,
        SIGNUP = 2,
        VERIFY = 3
    };
    STATE state = ZpForm::STATE::NONE;

    void apply_stylesheet();
    QTimer* fading_timer;
    QString username, password;
    //::FORM GRAPHICAL USER INTERFACE::\\
private:
    //STYLESHEET
    QFile File;
    QString FormStyleSheet;
    //KEEP ME IN DATA FILE
    QFile login_data;
    //SIGNUP FORM WIDGETS
    QLabel* signup_icon_label;
    QPixmap* signup_icon_map;
    QHBoxLayout* signup_icon_lay;
    QWidget* signup_icon_widg;
    QLabel* signup_topic_label;
    QHBoxLayout* signup_topic_lay;
    QWidget* signup_topic_widg;
    QLineEdit* signup_email_text;
    QLineEdit* signup_id_text;
    QLineEdit* signup_pass_text;
    QPushButton* signup_button;
    QHBoxLayout* signup_button_lay;
    QWidget* signup_button_widg;
    QVBoxLayout* signup_form_lay;
    QWidget* signup_form_widg;
    //LOGIN FORM WIDGETS
    QLabel* login_icon_label;
    QPixmap* login_icon_map;
    QHBoxLayout* login_icon_lay;
    QWidget* login_icon_widg;
    QLabel* login_topic_label;
    QHBoxLayout* login_topic_lay;
    QWidget* login_topic_widg;
    QLineEdit* login_id_text;
    QLineEdit* login_pass_text;
    QPushButton* login_button;
    QHBoxLayout* login_button_lay;
    QWidget* login_button_widg;
    QCheckBox* login_remember_checkbox;
    QHBoxLayout* login_remember_lay;
    QWidget* login_remember_widg;
    QVBoxLayout* login_form_lay;
    QWidget* login_form_widg;
    //WHOLE FORM WIDGETS
    QHBoxLayout* whole_lay;
    //QActions
    QAction* wrong_login_input_action_id;
    QAction* wrong_login_input_action_pass;
    QAction* wrong_signup_input_action_email;
    QAction* wrong_signup_input_action_id;
    QAction* wrong_signup_input_action_pass;
private:
    void create_form_widget();
    void is_kept_logged_in();
private slots:
    void slotLogin_Button_Clicked();
    void slotSignUp_Button_Clicked();
////////////////////////////////////////////////////

public:
//::VERIFYING GRAPHICAL USER INTERFACE::\\
private:
    QLabel* verify_icon_label;
    QPixmap* verify_icon_map;
    QHBoxLayout* verify_icon_lay;
    QWidget* verify_icon_widg;
    QLabel* verify_topic_label;
    QHBoxLayout* verify_topic_lay;
    QWidget* verify_topic_widg;
    QLabel* verify_descript_label;
    QHBoxLayout* verify_descript_lay;
    QWidget* verify_descript_widg;
    QLineEdit* verify_code_number;
    QPushButton* verify_button;
    QHBoxLayout* verify_button_lay;
    QWidget* verify_button_widg;
    QVBoxLayout* verify_form_lay;
    QWidget* verify_form_widg;
    QHBoxLayout* verify_final_lay;
    QAction* wrong_verify_input_action_number;
private:
    void create_verify_widget();
    int fading_percent = 100;
private slots:
    void slotFading_widget();
    void slotVerify_Button_Clicked();
public:

    //::NETWORKING::\\
private:
    QNetworkAccessManager* network;
    QNetworkRequest* request;
    QNetworkReply* reply;
private:
    void initiate_networking();
    void send_login_info();
    void send_signup_info(QString email);
    void send_verify_info(QString code);
    void handle_reply(QString _reply);
private slots:
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError err);
    void slotSslErrors(QList<QSslError> err);
////////////////////////////////////////////////////

//Outputs
signals:
    void login_validate(QString username, QString password);

public slots:
};

#endif // ZPFORM_H
