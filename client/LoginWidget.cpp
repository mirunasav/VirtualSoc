//
// Created by loghin on 01/12/22.
//

#include "LoginWidget.h"
#include <QKeyEvent>

LoginWidget ::LoginWidget(MainWindow *pParentWindow):
                        QWidget(pParentWindow),
                        pParent(pParentWindow){
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
    connect(this, SIGNAL(loginSuccess()), this->pParent, SLOT(swapWidgetsLoginSuccess()));
    connect(this->pSignUpButton, SIGNAL(clicked()), this, SLOT(onSignUp()));

    this->styleComponents();

    //aliniez titlul pe centru
    this->pLoginLayout->setAlignment(this->pWidgetTitle, Qt::AlignCenter);


}

void LoginWidget ::createComponents() {

    this-> pWidgetTitle = new QLabel( LoginWidget::pTitleLabelText, this);
    this-> pUsernameLabel = new QLabel(LoginWidget::pUsernameLabelText, this);
    this-> pPasswordLabel = new QLabel( LoginWidget::pPasswordLabelText, this);
    this-> pWidgetTitle = new QLabel(LoginWidget::pTitleLabelText, this);

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


void LoginWidget:: enterKeyPressEvent(QKeyEvent * event)
{
    if( event ->key() == Qt::Key_Return || event ->key() == Qt::Key_Enter)
    {
        this->onConfirmLogin();
    }
}

void LoginWidget ::settleLayouts() {
    //addWidget : obiect desenabil
    //addItem: layout pt ca nu e desenabil, chestii de aranjare, spacere
    this->pLoginLayout->addWidget(this->pWidgetTitle);
    this->pLoginLayout->addItem(this->pCredentialsLayout);

    this->pCredentialsLayout->addItem(this->pLabelLayout);
    this->pCredentialsLayout->addItem(this->pTextBoxLayout);
}

void LoginWidget ::styleComponents() {
    //daca vr sa fac styling in CSS la componente

}


