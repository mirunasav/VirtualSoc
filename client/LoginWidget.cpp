//
// Created by loghin on 01/12/22.
//

#include "LoginWidget.h"
#include "MainWindow.h"

#include <QKeyEvent>

LoginWidget ::LoginWidget(QWidget *pParentWindow):
                        QWidget(pParentWindow) {
    this->initWidget();

}

void LoginWidget ::initWidget() {
    this->createComponents();
    this->settleLayouts();
    this->adjustLayouts();

    //scriu cu bulinute parola
    this->pPasswordTextBox->setEchoMode(QLineEdit:: Password);

    //conectare componente:
    //daca apas login -> onConfirmLogin
    //if LoginSuccess -> MainWindow:: swapWidgetsLoginSuccess

    //daca apas signup -> onSignUp

    connect(this->pLoginButton, SIGNAL(clicked()), this, SLOT(onConfirmLogin()));
    connect(this, SIGNAL(loginSuccess()), this->parent(), SLOT(swapWidgetsLoginSuccess()));
    connect(this->pSignUpButton, SIGNAL(clicked()), this, SLOT(onSignUp()));

//    connect(this->pSignUpButton, & QPushButton :: clicked, [this]{
//        this->onSignUp();
//    });
//
//    connect (this->pSignUpButton, & QPushButton :: clicked, this, & LoginWidget :: onSignUp);

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

    this->pButtonsLayout = new QHBoxLayout(nullptr);
    this->pButtonsLayout ->setAlignment(Qt::AlignRight);

}



void LoginWidget ::settleLayouts() {
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

    this->pButtonsLayout->addWidget(this->pLoginButton);
    this->pButtonsLayout->addWidget(this->pSignUpButton);
}


void LoginWidget::adjustLayouts() {
    this->pLoginLayout->setAlignment(Qt::AlignCenter);
    this->pLoginLayout->setContentsMargins(MainWindow::WIDTH / 3, 0, MainWindow::WIDTH / 3, 0);

    this->setMinimumWidth( MainWindow::WIDTH / 3 * 2 + 200 );
    this->setMinimumHeight( MainWindow::HEIGHT / 2 );

    this->pLoginButton->setMaximumWidth( 75 );
    this->pLoginLayout->setAlignment( this->pLoginButton, Qt::AlignRight );

}
void LoginWidget ::styleComponents() {
    //daca vr sa fac styling in CSS la componente

}

void LoginWidget::onConfirmLogin() {
    emit this->loginSuccess();
}

void LoginWidget ::onSignUp() {

}
void LoginWidget:: enterKeyPressEvent(QKeyEvent * event)
{
    if( event ->key() == Qt::Key_Return || event ->key() == Qt::Key_Enter)
    {
        this->onConfirmLogin();
    }
}

bool LoginWidget::validateInput() {
    return true;
}


