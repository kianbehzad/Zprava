#include "zpform.h"

ZpForm::ZpForm(bool check_remember_me, QWidget *parent) : QWidget(parent)
{

    //stylesheet
    apply_stylesheet();

    //creatin all widgets
    create_form_widget();

    //network
    initiate_networking();

    //keep me logged in
    if(check_remember_me)
        is_kept_logged_in();

}

void ZpForm::apply_stylesheet()
{
    //getting style sheets
    File.setFileName(":/form_stylesheet.qss");
    qDebug() << "is qt form_stylesheet opend: " <<File.open(QFile::ReadOnly);
    FormStyleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(FormStyleSheet);
    File.close();

}

void ZpForm::create_form_widget()
{
    //SIGNUP
    //top icon
    signup_icon_label = new QLabel();
    signup_icon_label->setObjectName("icon_label");
    signup_icon_map = new QPixmap(":/signup.png");
    signup_icon_label->setPixmap(*signup_icon_map);
    signup_icon_label->setMaximumSize(100, 100);
    signup_icon_lay = new QHBoxLayout();
    signup_icon_lay->addWidget(signup_icon_label);
    signup_icon_lay->setAlignment(signup_icon_label, Qt::AlignCenter);
    signup_icon_widg = new QWidget();
    signup_icon_widg->setLayout(signup_icon_lay);

    //topic name
    signup_topic_label = new QLabel();
    signup_topic_label->setText("SIGN UP");
    signup_topic_label->setObjectName("topic_label");
    signup_topic_lay = new QHBoxLayout();
    signup_topic_lay->addWidget(signup_topic_label);
    signup_topic_lay->setAlignment(signup_topic_label, Qt::AlignCenter);
    signup_topic_widg = new QWidget();
    signup_topic_widg->setLayout(signup_topic_lay);

    //inputs
    signup_email_text = new QLineEdit();
    signup_email_text->setObjectName("input_text");
    signup_email_text->setPlaceholderText("Email Address");
    signup_id_text = new QLineEdit();
    signup_id_text->setObjectName("input_text");
    signup_id_text->setPlaceholderText("User Id");
    signup_pass_text = new QLineEdit();
    signup_pass_text->setEchoMode(QLineEdit::Password);
    signup_pass_text->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    signup_pass_text->setObjectName("input_text");
    signup_pass_text->setPlaceholderText("Password");

    //submit button
    signup_button = new QPushButton();
    signup_button->setObjectName("submit_button");
    signup_button->setText("Sign up");
    signup_button_lay = new QHBoxLayout();
    signup_button_lay->addWidget(signup_button);
    signup_button_lay->setAlignment(signup_button, Qt::AlignCenter);
    signup_button_widg = new QWidget();
    signup_button_widg->setLayout(signup_button_lay);

    //final form
    signup_form_lay = new QVBoxLayout();
    signup_form_lay->addWidget(signup_icon_widg);
    signup_form_lay->addWidget(signup_topic_widg);
    signup_form_lay->addWidget(signup_email_text);
    signup_form_lay->addWidget(signup_id_text);
    signup_form_lay->addWidget(signup_pass_text);
    signup_form_lay->addWidget(signup_button_widg);
    signup_form_widg = new QWidget();
    signup_form_widg->setObjectName("form_widg");
    signup_form_widg->setLayout(signup_form_lay);



    //LOGIN
    //top icon
    login_icon_label = new QLabel();
    login_icon_label->setObjectName("icon_label");
    login_icon_map = new QPixmap(":/login.png");
    login_icon_label->setPixmap(*login_icon_map);
    login_icon_label->setMaximumSize(100, 100);
    login_icon_lay = new QHBoxLayout();
    login_icon_lay->addWidget(login_icon_label);
    login_icon_lay->setAlignment(login_icon_label, Qt::AlignCenter);
    login_icon_widg = new QWidget();
    login_icon_widg->setLayout(login_icon_lay);

    //topic name
    login_topic_label = new QLabel();
    login_topic_label->setText("LOG IN");
    login_topic_label->setObjectName("topic_label");
    login_topic_lay = new QHBoxLayout();
    login_topic_lay->addWidget(login_topic_label);
    login_topic_lay->setAlignment(login_topic_label, Qt::AlignCenter);
    login_topic_widg = new QWidget();
    login_topic_widg->setLayout(login_topic_lay);

    //inputs
    login_id_text = new QLineEdit();
    login_id_text->setObjectName("input_text");
    login_id_text->setPlaceholderText("User Id");
    login_pass_text = new QLineEdit();
    login_pass_text->setEchoMode(QLineEdit::Password);
    login_pass_text->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    login_pass_text->setObjectName("input_text");
    login_pass_text->setPlaceholderText("Password");

    //remember me checkbox
    login_remember_checkbox = new QCheckBox();
    login_remember_checkbox->setObjectName("checkbox");
    login_remember_checkbox->setText("Remember Me");
    login_forgot_button = new QPushButton();
    login_forgot_button->setObjectName("forgot_button");
    login_forgot_button->setText("Forgot My Password");
    login_option_lay = new QHBoxLayout();
    login_option_lay->addWidget(login_remember_checkbox);
    login_option_lay->addWidget(login_forgot_button);
    login_option_widg = new QWidget();
    login_option_widg->setObjectName("login_option");
    login_option_widg->setFixedHeight(38);
    login_option_widg->setLayout(login_option_lay);

    //submit button
    login_button = new QPushButton();
    login_button->setObjectName("submit_button");
    login_button->setText("Login");
    login_button_lay = new QHBoxLayout();
    login_button_lay->addWidget(login_button);
    login_button_lay->setAlignment(login_button, Qt::AlignCenter);
    login_button_widg = new QWidget();
    login_button_widg->setLayout(login_button_lay);

    //final form
    login_form_lay = new QVBoxLayout();
    login_form_lay->addWidget(login_icon_widg);
    login_form_lay->addWidget(login_topic_widg);
    login_form_lay->addSpacing(20);
    login_form_lay->addWidget(login_id_text);
    login_form_lay->addWidget(login_pass_text);
    //login_form_lay->addSpacing(20);
    login_form_lay->addWidget(login_option_widg);
    login_form_lay->addWidget(login_button_widg);
    login_form_widg = new QWidget();
    login_form_widg->setObjectName("form_widg");
    login_form_widg->setLayout(login_form_lay);


    //WHOLE FORM
    whole_lay = new QHBoxLayout();
    whole_lay->addWidget(signup_form_widg);
    whole_lay->setSpacing(100);
    whole_lay->addWidget(login_form_widg);
    whole_form_widg = new QWidget();
    whole_form_widg->setLayout(whole_lay);
    mother_lay = new QHBoxLayout();
    mother_lay->addWidget(whole_form_widg);
    if(this->layout() != nullptr)//TODO must delete all containig widgets
        delete this->layout();
    this->setLayout(mother_lay);

    connect(login_button, SIGNAL(clicked(bool)), this, SLOT(slotLogin_Button_Clicked()));
    connect(signup_button, SIGNAL(clicked(bool)), this, SLOT(slotSignUp_Button_Clicked()));
    connect(login_forgot_button, SIGNAL(clicked(bool)), this, SLOT(slotLogin_ForgotButton_Clicked()));

    wrong_signup_input_action_email = nullptr;
    wrong_signup_input_action_id = nullptr;
    wrong_signup_input_action_pass = nullptr;
    wrong_login_input_action_id = nullptr;
    wrong_login_input_action_pass = nullptr;
}

void ZpForm::slotLogin_Button_Clicked()
{
    bool isCorrect = true;
    if(wrong_login_input_action_id != nullptr)
        login_id_text->removeAction(wrong_login_input_action_id);
    if(wrong_login_input_action_pass != nullptr)
        login_pass_text->removeAction(wrong_login_input_action_pass);
    QString id = login_id_text->text();
    QString pass = login_pass_text->text();
    if(id == "")
    {
        isCorrect = false;
        //login_id_text->setClearButtonEnabled(true);
        wrong_login_input_action_id = login_id_text->addAction(QIcon(":/Red_X.png"), QLineEdit::TrailingPosition);
    }
    if(pass == "")
    {
        isCorrect = false;
        //login_pass_text->setClearButtonEnabled(true);
        wrong_login_input_action_pass = login_pass_text->addAction(QIcon(":/Red_X.png"), QLineEdit::TrailingPosition);
    }
    if(isCorrect)
    {
        username = id;  password = pass;
        if(login_remember_checkbox->isChecked())
        {
            login_data.setFileName(qApp->applicationDirPath() + "/login_data.txt");
            bool is_opened = login_data.open(QFile::WriteOnly);
            qDebug() << "is login_data: " << is_opened;
            if (is_opened)
            {
                 QTextStream out(&login_data);
                 // line 1 -->username , line2 --> password
                 out << username << "\n" << password << "\n";
            }
            login_data.close();
        }
        send_login_info();
    }
}

void ZpForm::slotSignUp_Button_Clicked()
{
    bool isCorrect = true;
    if(wrong_signup_input_action_email != nullptr)
        signup_email_text->removeAction(wrong_signup_input_action_email);
    if(wrong_signup_input_action_id != nullptr)
        signup_id_text->removeAction(wrong_signup_input_action_id);
    if(wrong_signup_input_action_pass != nullptr)
        signup_pass_text->removeAction(wrong_signup_input_action_pass);
    QString email = signup_email_text->text();
    QString id = signup_id_text->text();
    QString pass = signup_pass_text->text();
    if(email == "")
    {
        isCorrect = false;
        //signup_email_text->setClearButtonEnabled(true);
        wrong_signup_input_action_email = signup_email_text->addAction(QIcon(":/Red_X.png"), QLineEdit::TrailingPosition);
    }
    if(id == "")
    {
        isCorrect = false;
        //signup_id_text->setClearButtonEnabled(true);
        wrong_signup_input_action_id = signup_id_text->addAction(QIcon(":/Red_X.png"), QLineEdit::TrailingPosition);
    }
    if(pass == "")
    {
        isCorrect = false;
        //signup_pass_text->setClearButtonEnabled(true);
        wrong_signup_input_action_pass = signup_pass_text->addAction(QIcon(":/Red_X.png"), QLineEdit::TrailingPosition);
    }
    if(isCorrect)
    {
        username = id;  password = pass;
        send_signup_info(email);
    }
}

void ZpForm::slotLogin_ForgotButton_Clicked()
{
    fading_timer = new QTimer(this);
    connect(fading_timer, SIGNAL(timeout()), this, SLOT(slotFading_formTOforget_widget()));
    fading_timer->start(30);
}

void ZpForm::create_verify_widget()
{
    //VERIFY
    //top icon
    verify_icon_label = new QLabel();
    verify_icon_label->setObjectName("icon_label");
    verify_icon_map = new QPixmap(":/verifying.png");
    verify_icon_label->setPixmap(*verify_icon_map);
    verify_icon_label->setMaximumSize(100, 100);
    verify_icon_lay = new QHBoxLayout();
    verify_icon_lay->addWidget(verify_icon_label);
    verify_icon_lay->setAlignment(verify_icon_label, Qt::AlignCenter);
    verify_icon_widg = new QWidget();
    verify_icon_widg->setLayout(verify_icon_lay);

    //topic name
    verify_topic_label = new QLabel();
    verify_topic_label->setText("VERIFICATION CODE");
    verify_topic_label->setObjectName("topic_label");
    verify_topic_lay = new QHBoxLayout();
    verify_topic_lay->addWidget(verify_topic_label);
    verify_topic_lay->setAlignment(verify_topic_label, Qt::AlignCenter);
    verify_topic_widg = new QWidget();
    verify_topic_widg->setLayout(verify_topic_lay);

    //description label
    verify_descript_label = new QLabel();
    verify_descript_label->setText("Please Enter The Verification Code We Have Just Sent To Your Email!");
    verify_descript_label->setObjectName("description_label");
    verify_descript_lay = new QHBoxLayout();
    verify_descript_lay->addWidget(verify_descript_label);
    verify_descript_lay->setAlignment(verify_descript_label, Qt::AlignCenter);
    verify_descript_widg = new QWidget();
    verify_descript_widg->setLayout(verify_descript_lay);

    //inputs
    verify_code_number = new QLineEdit();
    verify_code_number->setObjectName("input_number");
    verify_code_number->setPlaceholderText("Verification Code");

    //submit button
    verify_button = new QPushButton();
    verify_button->setObjectName("submit_button");
    verify_button->setText("Verify");
    verify_button_lay = new QHBoxLayout();
    verify_button_lay->addWidget(verify_button);
    verify_button_lay->setAlignment(verify_button, Qt::AlignCenter);
    verify_button_widg = new QWidget();
    verify_button_widg->setLayout(verify_button_lay);

    //final form
    verify_form_lay = new QVBoxLayout();
    verify_form_lay->addWidget(verify_icon_widg);
    verify_form_lay->addWidget(verify_topic_widg);
    verify_form_lay->addWidget(verify_descript_widg);
    verify_form_lay->addWidget(verify_code_number);
    verify_form_lay->addWidget(verify_button_widg);
    verify_form_widg = new QWidget();
    verify_form_widg->setObjectName("form_widg");
    verify_form_widg->setLayout(verify_form_lay);
    verify_final_lay = new QHBoxLayout();
    verify_final_lay->addWidget(verify_form_widg);
    if(this->layout() != nullptr)//TODO must delete all containig widgets
        delete this->layout();
    this->setLayout(verify_final_lay);

    connect(verify_button, SIGNAL(clicked(bool)), this, SLOT(slotVerify_Button_Clicked()));

    wrong_verify_input_action_number = nullptr;

}

void ZpForm::slotFading_formTOverify_widget()
{
    fading_formTOverify_percent -=10;
    if(fading_formTOverify_percent > 0)
    {
        QString fading_style{"QWidget#form_widg{background-color: rgba(0%, 0%, 0%, "+QString::number(fading_formTOverify_percent)+"%);}"};
        login_form_widg->setStyleSheet(fading_style);
        signup_form_widg->setStyleSheet(fading_style);
    }
    else if(fading_formTOverify_percent == 0)
    {
        this->setStyleSheet(FormStyleSheet);
        whole_form_widg->hide();
        create_verify_widget();
        fading_formTOverify_percent = 100;
        fading_timer->stop();
        return;
    }

}

void ZpForm::slotFading_formTOforget_widget()
{
    fading_formTOforget_percent -=10;
    if(fading_formTOforget_percent > 0)
    {
        QString fading_style{"QWidget#form_widg{background-color: rgba(0%, 0%, 0%, "+QString::number(fading_formTOforget_percent)+"%);}"};
        login_form_widg->setStyleSheet(fading_style);
        signup_form_widg->setStyleSheet(fading_style);
    }
    else if(fading_formTOforget_percent == 0)
    {
        this->setStyleSheet(FormStyleSheet);
        whole_form_widg->hide();
        create_forget_widget();
        fading_formTOforget_percent = 100;
        fading_timer->stop();
        return;
    }
}

void ZpForm::slotFading_forgetTOform_widget()
{
    fading_forgetTOform_percent -=10;
    if(fading_forgetTOform_percent > 0)
    {
        QString fading_style{"QWidget#form_widg{background-color: rgba(0%, 0%, 0%, "+QString::number(fading_forgetTOform_percent)+"%);}"};
        forget_form_widg->setStyleSheet(fading_style);
    }
    else if(fading_forgetTOform_percent == 0)
    {
        this->setStyleSheet(FormStyleSheet);
        forget_form_widg->hide();
        create_form_widget();
        fading_forgetTOform_percent = 100;
        fading_timer->stop();
        return;
    }
}

void ZpForm::slotForget_Button_Clicked()
{
    bool isCorrect = true;
    if(wrong_forget_input_action_number != nullptr)
        forget_email_text->removeAction(wrong_forget_input_action_number);
    QString email = forget_email_text->text();
    if(email == "")
    {
        isCorrect = false;
        //login_id_text->setClearButtonEnabled(true);
        wrong_forget_input_action_number = forget_email_text->addAction(QIcon(":/Red_X.png"), QLineEdit::TrailingPosition);
    }
    if(isCorrect)
    {
        send_forget_info(email);
    }
}

void ZpForm::slotVerify_Button_Clicked()
{
    bool isCorrect = true;
    if(wrong_verify_input_action_number != nullptr)
        verify_code_number->removeAction(wrong_verify_input_action_number);
    QString code = verify_code_number->text();
    if(code == "")
    {
        isCorrect = false;
        //login_id_text->setClearButtonEnabled(true);
        wrong_verify_input_action_number = verify_code_number->addAction(QIcon(":/Red_X.png"), QLineEdit::TrailingPosition);
    }
    if(isCorrect)
    {
        send_verify_info(code);
    }
}

void ZpForm::create_forget_widget()
{
    //FORGET
    //top icon
    forget_icon_label = new QLabel();
    forget_icon_label->setObjectName("icon_label");
    forget_icon_map = new QPixmap(":/verifying.png");
    forget_icon_label->setPixmap(*forget_icon_map);
    forget_icon_label->setMaximumSize(100, 100);
    forget_icon_lay = new QHBoxLayout();
    forget_icon_lay->addWidget(forget_icon_label);
    forget_icon_lay->setAlignment(forget_icon_label, Qt::AlignCenter);
    forget_icon_widg = new QWidget();
    forget_icon_widg->setLayout(forget_icon_lay);

    //topic name
    forget_topic_label = new QLabel();
    forget_topic_label->setText("FORGET PASSWORD");
    forget_topic_label->setObjectName("topic_label");
    forget_topic_lay = new QHBoxLayout();
    forget_topic_lay->addWidget(forget_topic_label);
    forget_topic_lay->setAlignment(forget_topic_label, Qt::AlignCenter);
    forget_topic_widg = new QWidget();
    forget_topic_widg->setLayout(forget_topic_lay);

    //description label
    forget_descript_label = new QLabel();
    forget_descript_label->setText("Please Enter Your Email Address And We Will Send Your Data!");
    forget_descript_label->setObjectName("description_label");
    forget_descript_lay = new QHBoxLayout();
    forget_descript_lay->addWidget(forget_descript_label);
    forget_descript_lay->setAlignment(forget_descript_label, Qt::AlignCenter);
    forget_descript_widg = new QWidget();
    forget_descript_widg->setLayout(forget_descript_lay);

    //inputs
    forget_email_text = new QLineEdit();
    forget_email_text->setObjectName("input_number");
    forget_email_text->setPlaceholderText("Email Address");

    //submit button
    forget_button = new QPushButton();
    forget_button->setObjectName("submit_button");
    forget_button->setText("Send");
    forget_button_lay = new QHBoxLayout();
    forget_button_lay->addWidget(forget_button);
    forget_button_lay->setAlignment(forget_button, Qt::AlignCenter);
    forget_button_widg = new QWidget();
    forget_button_widg->setLayout(forget_button_lay);

    //final form
    forget_form_lay = new QVBoxLayout();
    forget_form_lay->addWidget(forget_icon_widg);
    forget_form_lay->addWidget(forget_topic_widg);
    forget_form_lay->addWidget(forget_descript_widg);
    forget_form_lay->addWidget(forget_email_text);
    forget_form_lay->addWidget(forget_button_widg);
    forget_form_widg = new QWidget();
    forget_form_widg->setObjectName("form_widg");
    forget_form_widg->setLayout(forget_form_lay);
    forget_final_lay = new QHBoxLayout();
    forget_final_lay->addWidget(forget_form_widg);
    if(this->layout() != nullptr)//TODO must delete all containig widgets
        delete this->layout();
    this->setLayout(forget_final_lay);

    connect(forget_button, SIGNAL(clicked(bool)), this, SLOT(slotForget_Button_Clicked()));

    wrong_forget_input_action_number = nullptr;
}

void ZpForm::initiate_networking()
{
    network = new QNetworkAccessManager();
    request = new QNetworkRequest();
    request->setUrl(QUrl("http://127.0.0.1:8000/signup/hello/"));
    reply = network->get(*request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));
}

void ZpForm::send_login_info()
{
    state = ZpForm::STATE::LOGIN;
    request->setUrl(QUrl("http://127.0.0.1:8000/login/login/?username="+username+"&&password="+password));
    reply = network->get(*request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));
}

void ZpForm::send_signup_info(QString email)
{
    state = ZpForm::STATE::SIGNUP;
    request->setUrl(QUrl("http://127.0.0.1:8000/signup/registration/?username="+username+"&&password="+password+"&&email="+email));
    reply = network->get(*request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));
}

void ZpForm::send_verify_info(QString code)
{
    state = ZpForm::STATE::VERIFY;
    request->setUrl(QUrl("http://127.0.0.1:8000/signup/verification/?username="+username+"&&verification_code="+code));
    reply = network->get(*request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));
}

void ZpForm::send_forget_info(QString email)
{
    state = ZpForm::STATE::FORGET;
    request->setUrl(QUrl("http://127.0.0.1:8000/login/forget/?email="+email));
    reply = network->get(*request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),   this, SLOT(slotError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),          this, SLOT(slotSslErrors(QList<QSslError>)));
}

void ZpForm::is_kept_logged_in()
{
    login_data.setFileName(qApp->applicationDirPath() + "/login_data.txt");
    bool is_opened = login_data.open(QFile::ReadOnly);
    qDebug() << "is login_data: " << is_opened;
    if (is_opened)
    {
            QTextStream in(&login_data);
            // line 1 -->username , line2 --> password
            in>>username;
            in>>password;
            send_login_info();
    }

}

void ZpForm::handle_reply(QString _reply)//TODO for just returning states
{
    switch (state) {
    case ZpForm::STATE::NONE:

        break;
    case ZpForm::STATE::SIGNUP:
    {
        if(_reply == "Incomplete")
            return;
        else if(_reply == "EmailExist")
        {
            if(wrong_signup_input_action_email != nullptr)
                signup_email_text->removeAction(wrong_signup_input_action_email);
            wrong_signup_input_action_email = signup_email_text->addAction(QIcon(":/Exclamation_sign.png"), QLineEdit::TrailingPosition);
        }
        else if(_reply == "UsernameExist")
        {
            if(wrong_signup_input_action_id != nullptr)
                signup_id_text->removeAction(wrong_signup_input_action_id);
            wrong_signup_input_action_id = signup_id_text->addAction(QIcon(":/Exclamation_sign.png"), QLineEdit::TrailingPosition);
        }
        else if(_reply == "BothExist")
        {
            if(wrong_signup_input_action_email != nullptr)
                signup_email_text->removeAction(wrong_signup_input_action_email);
            if(wrong_signup_input_action_id != nullptr)
                signup_id_text->removeAction(wrong_signup_input_action_id);
            wrong_signup_input_action_id = signup_id_text->addAction(QIcon(":/Exclamation_sign.png"), QLineEdit::TrailingPosition);
            wrong_signup_input_action_email = signup_email_text->addAction(QIcon(":/Exclamation_sign.png"), QLineEdit::TrailingPosition);
        }
        else if(_reply == "pre_verified")
        {
            fading_timer = new QTimer(this);
            connect(fading_timer, SIGNAL(timeout()), this, SLOT(slotFading_formTOverify_widget()));
            fading_timer->start(30);
        }
    }
        break;
    case ZpForm::STATE::LOGIN:
    {
        if(_reply == "Incomplete")
            return;
        else if(_reply == "InvalidUsername")
        {
            if(wrong_login_input_action_id != nullptr)
                login_id_text->removeAction(wrong_login_input_action_id);
            wrong_login_input_action_id = login_id_text->addAction(QIcon(":/Exclamation_sign.png"), QLineEdit::TrailingPosition);
        }
        else if(_reply == "NotValidate")
        {
            if(wrong_login_input_action_id != nullptr)
                login_id_text->removeAction(wrong_login_input_action_id);
            if(wrong_login_input_action_pass != nullptr)
                login_pass_text->removeAction(wrong_login_input_action_pass);
            wrong_login_input_action_id = login_id_text->addAction(QIcon(":/Exclamation_sign.png"), QLineEdit::TrailingPosition);
            wrong_login_input_action_pass = login_pass_text->addAction(QIcon(":/Exclamation_sign.png"), QLineEdit::TrailingPosition);
        }
        else if(_reply == "InvalidPassword")
        {
            if(wrong_login_input_action_pass != nullptr)
                login_pass_text->removeAction(wrong_login_input_action_pass);
            wrong_login_input_action_pass = login_pass_text->addAction(QIcon(":/Exclamation_sign.png"), QLineEdit::TrailingPosition);
        }
        else if(_reply == "Enter")
        {
            emit login_validate(username, password);
        }
    }
        break;
    case ZpForm::STATE::VERIFY:
    {
        if(_reply == "Incomplete")
            return;
        else if(_reply == "InvalidUsername")
            return;
        else if(_reply == "InvalidCode")
        {
            if(wrong_verify_input_action_number != nullptr)
                verify_code_number->removeAction(wrong_verify_input_action_number);
            wrong_verify_input_action_number = verify_code_number->addAction(QIcon(":/Exclamation_sign.png"), QLineEdit::TrailingPosition);
        }
        else if(_reply == "Enter")
        {
            emit login_validate(username, password);
        }
    }
    case ZpForm::STATE::FORGET:
    {
        if(_reply == "Incomplete")
            return;
        else if(_reply == "InvalidEmail")
        {
            if(wrong_forget_input_action_number != nullptr)
                forget_email_text->removeAction(wrong_forget_input_action_number);
            wrong_forget_input_action_number = forget_email_text->addAction(QIcon(":/Exclamation_sign.png"), QLineEdit::TrailingPosition);
        }
        else if(_reply == "Sent")
        {
            fading_timer = new QTimer(this);
            connect(fading_timer, SIGNAL(timeout()), this, SLOT(slotFading_forgetTOform_widget()));
            fading_timer->start(30);
        }
    }
    default:
        break;
    }
}

void ZpForm::slotReadyRead()
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
            qDebug() <<"-> read ok";//TODO: in QLabel
        }

        allbuf += & buf[0];
    }

    reply_string = allbuf;
    qDebug() <<reply_string;//TODO remove this
    handle_reply(reply_string);
}

void ZpForm::slotError(QNetworkReply::NetworkError err)
{
    //TODO: in QLabel
    qDebug() << "network error" << err;
}

void ZpForm::slotSslErrors(QList<QSslError> err)
{
    //TODO: in QLabel
    qDebug() << "unknown network error";

}
