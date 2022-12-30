#include "LoginWidget.h"
#include "MainWindow.h"
#include "ServerConnection.h"
#include <QKeyEvent>
#include <QMessageBox>

using namespace common;

LoginWidget ::LoginWidget(QWidget *pParent):
                        QWidget(pParent)
{
    this->initWidget();

}

void LoginWidget ::initWidget() {
    this->createComponents();
    this->settleLayouts();
    this->adjustLayouts();

    this->pPasswordTextBox->setEchoMode(QLineEdit:: Password);
    //conectare componente:
    //daca apas login -> onConfirmLogin
    //if LoginSuccess -> MainWindow:: swapWidgetsLoginSuccess
    //daca apas signup -> onSignUp

    //connect(this->pLoginButton, SIGNAL(clicked()), this, SLOT(onConfirmLogin()));
    //in varianta de mai sus, nu verifica daca exista semnalul respectiv; in varianta de mai jos, da, e mai safe
   this->connectComponents();

    this->styleComponents();
    //aliniez titlul pe centru
    this->pLoginLayout->setAlignment(this->pWidgetTitle, Qt::AlignCenter);

}

void LoginWidget ::createComponents() {

    this-> pWidgetTitle = new QLabel( LoginWidget::pTitleLabelText, this);
    this-> pUsernameLabel = new QLabel(LoginWidget::pUsernameLabelText, this);
    this-> pPasswordLabel = new QLabel( LoginWidget::pPasswordLabelText, this);

    this-> pUsernameTextBox = new QLineEdit(this);
    this-> pPasswordTextBox = new QLineEdit(this);

    this->pLoginLayout = new QVBoxLayout (this);
    this->pCredentialsLayout = new QHBoxLayout (nullptr);

    this->pLabelLayout = new QVBoxLayout (nullptr);
    this->pTextBoxLayout = new QVBoxLayout(nullptr);

    this->pLoginButton = new QPushButton(LoginWidget ::pLoginButtonText,this);
    this->pSignUpButton = new QPushButton (LoginWidget ::pSignUpButtonText, this);
    this->pContinueWithoutLogginInButton = new QPushButton(LoginWidget :: pContinueWithoutLogginInButtonText, this);

    this->pButtonsLayout = new QVBoxLayout(nullptr);
    this->pButtonsLayout->setAlignment(Qt::AlignRight);

    this->pLoginButtonsLayout = new QHBoxLayout(nullptr);
    this->pLoginButtonsLayout ->setAlignment(Qt::AlignRight);
}

void LoginWidget :: settleLayouts () {
    //addWidget : obiect desenabil
    //addItem: layout pt ca nu e desenabil, chestii de aranjare, spacere
    this->pLoginLayout->addWidget(this->pWidgetTitle);
    this->pLoginLayout->addItem(this->pCredentialsLayout);

    this->pCredentialsLayout->addItem(this->pLabelLayout);
    this->pCredentialsLayout->addItem(this->pTextBoxLayout);

    this->pTextBoxLayout->addWidget(this->pUsernameTextBox);
    this->pTextBoxLayout->addWidget(this->pPasswordTextBox);

    this->pLabelLayout->addWidget(this->pUsernameLabel);
    this->pLabelLayout->addWidget(this->pPasswordLabel);

    this->pLoginLayout->addItem(this->pButtonsLayout);

    this->pButtonsLayout->addItem(this->pLoginButtonsLayout);
    this->pButtonsLayout->addWidget(this->pContinueWithoutLogginInButton);

    this->pLoginButtonsLayout->addWidget(this->pLoginButton);
    this->pLoginButtonsLayout->addWidget(this->pSignUpButton);
}


void LoginWidget::adjustLayouts() {
    this->pLoginLayout->setAlignment(Qt::AlignCenter);
    this->pLoginLayout->setContentsMargins(MainWindow::WIDTH / 3, 0, MainWindow::WIDTH / 3, 0);

    this->setMinimumWidth( MainWindow::WIDTH / 3 * 2 + 200 );
    this->setMinimumHeight( MainWindow::HEIGHT / 2 );

    this->pLoginButton->setMaximumWidth( 75 );
    this->pLoginLayout->setAlignment( this->pLoginButton, Qt::AlignRight );

}

void LoginWidget::connectComponents() {
    connect(this->pLoginButton, &QPushButton :: clicked, this, &LoginWidget ::onConfirmLogin);
    connect(this, SIGNAL(loginSuccess()), this->parent(), SLOT(swapWidgetsLoginSuccess()));
    connect(this->pSignUpButton, & QPushButton :: clicked, [this]{
        this->onSignUp();
    });//cu lambda functii

    connect(this->pContinueWithoutLogginInButton, &QPushButton ::clicked, [this]{
        this->onSkip();
    });
    connect(this, SIGNAL(notLoggedIn()), this->parent(), SLOT(swapWidgetsSkip()));
}



void LoginWidget ::styleComponents() {
    //daca vr sa fac styling in CSS la componente; aparent nu e nevoie, face qt singur

}

void LoginWidget::onConfirmLogin() {
    if(!validateInput())
        return;
    //daca inputul e bun, trebuie sa verificam in fisierul cu username si parola
    //daca le gasim pe cele introduse de user

    ServerConnection::getInstance().connect(common::SERVER_IP, common::SERVER_PORT);

    if(!ServerConnection::getInstance().isConnected()) //nu a mers conexiunea
    {
        this->notificationPopUp(LoginWidget::pServerDown);
        return;
    }
    std::string username = this->pUsernameTextBox->text().toStdString();
    std::string password = this->pPasswordTextBox->text().toStdString();

    writeRequest(ServerConnection::getInstance().getSocket(), ClientRequests ::REQUEST_LOGIN);//scriu ce tip de request este
    writeString(ServerConnection::getInstance().getSocket(), this->pUsernameTextBox->text().toStdString());//scriu username
    writeString(ServerConnection::getInstance().getSocket(), this->pPasswordTextBox->text().toStdString());//scriu parola

    ServerResponse response  = common::readResponse(ServerConnection::getInstance().getSocket());

    switch(response)
    {
        case ServerResponse::LOGIN_BAD_USER_PASS :
            this->notificationPopUp(LoginWidget ::pMessageLoginFailed);
            break;
        case ServerResponse:: LOGIN_USER_ALREADY_CONNECTED:
            this->notificationPopUp(LoginWidget :: pMessageUserAlreadyConnected);
            break;
        default:
            emit this->loginSuccess();
    }

}

void LoginWidget ::onSignUp() {
    //verific daca usernameul este valabil; daca este, atunci apare un pop up cu
    //"account created" si apoi fac login;
    if(!validateInput())
    {
        return;
    }


    ServerConnection::getInstance().connect(common::SERVER_IP, common::SERVER_PORT);

    if(!ServerConnection::getInstance().isConnected()) //nu a mers conexiunea
    {
        this->notificationPopUp(LoginWidget::pServerDown);
        return;
    }

    std::string username = this->pUsernameTextBox->text().toStdString().c_str();
    std::string password = this->pPasswordTextBox->text().toStdString().c_str();

    writeRequest(ServerConnection::getInstance().getSocket(), ClientRequests ::REQUEST_SIGN_UP);
    writeString(ServerConnection::getInstance().getSocket(), this->pUsernameTextBox->text().toStdString());//scriu username
    writeString(ServerConnection::getInstance().getSocket(), this->pPasswordTextBox->text().toStdString());//scriu parola

    ServerResponse response  = common::readResponse(ServerConnection::getInstance().getSocket());

    switch(response)
    {
        case ServerResponse::CREATE_ACCOUNT_USERNAME_EXISTS :
            this->notificationPopUp(LoginWidget ::pMessageSignUpFailed);
            break;
        case ServerResponse:: CREATE_ACCOUNT_SUCCESS:
            this->notificationPopUp(LoginWidget :: pMessageAccountCreated);
            emit this->loginSuccess();
    }


}

void LoginWidget::onSkip() {
    emit this->notLoggedIn();
}

void LoginWidget::keyPressEvent(QKeyEvent * event)
{
    if( event ->key() == Qt::Key_Return || event ->key() == Qt::Key_Enter)
    {
        this->onConfirmLogin();
    }
}

bool LoginWidget::validateInput() {
    //verificam daca vreunul dintre fieldurile username si password sunt empty
    if(this->pUsernameTextBox->text().isEmpty())
    {
        this->notificationPopUp(LoginWidget::pUsernameLabelEmpty);
        return false;
    }
    if(this->pPasswordTextBox->text().isEmpty())
        {       this->notificationPopUp(LoginWidget::pPasswordLabelEmpty);
        return false;
    }
    if(this->pUsernameTextBox->text().contains('|') ||
       this->pUsernameTextBox->text().contains(' ') ||
       this->pUsernameTextBox->text().contains('\n') )
    {
        this->notificationPopUp(LoginWidget::pMessageInvalidCharacters);
        return false;
    }
    return true;
}

void LoginWidget::notificationPopUp(const char *message) {
    //apare un text box pop up; parintele este this
    //titlul este ..., mesajul este message, un buton de ok
    QMessageBox::information(this, " ", message,QMessageBox::Ok);

}
