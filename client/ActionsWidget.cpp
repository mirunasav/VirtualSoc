//
// Created by mrnk on 12/2/22.
//

#include <QVBoxLayout>
#include <QMenuBar>
#include "ActionsWidget.h"
#include "MainWindow.h"
#include "ServerConnection.h"
ActionsWidget:: ActionsWidget(QWidget *pParentWindow) : QWidget(pParentWindow)
{
    this->initWidget();
}

void ActionsWidget::initWidget()
{
    this->createComponents();
    this->settleLayouts();
    this->adjustLayouts();

    connect(this->pLogoutButton, &QPushButton ::clicked, this, &ActionsWidget::onLogout);
    connect(this, SIGNAL(loggedOut()), this->parent(), SLOT(swapWidgetsLogOut()));

    connect(this->pFriendsButton, &QPushButton ::clicked, this, &ActionsWidget::onFriendsButton);
    connect(this, SIGNAL(goToFriendsMenu()), this->parent(), SLOT(swapWidgetsFriendsMenu()));
}

void ActionsWidget::createComponents() {

    this->pActionsLayout = new QVBoxLayout(this);

    this->pMyProfileButton = new QPushButton(ActionsWidget::pMyProfileButtonText, this);
    this->pPostButton = new QPushButton(ActionsWidget::pPostButtonText, this);
    this->pFriendsButton = new QPushButton(ActionsWidget::pFriendsButtonText, this);
    this->pMessagesButton = new QPushButton(ActionsWidget::pMessagesButtonText, this);
    this->pSettingsButton = new QPushButton(ActionsWidget::pSettingsButtonText, this);
    this->pLogoutButton = new QPushButton(ActionsWidget:: pLogoutButtonText, this);
}

void ActionsWidget::settleLayouts() {
    this->pActionsLayout->addWidget(this->pMyProfileButton);
    this->pActionsLayout->addWidget(this->pPostButton);
    this->pActionsLayout->addWidget(this->pFriendsButton);
    this->pActionsLayout->addWidget(this->pMessagesButton);
    this->pActionsLayout->addWidget(this->pSettingsButton);
    this->pActionsLayout->addWidget(this->pLogoutButton);

}

void ActionsWidget::adjustLayouts() {

    this->pActionsLayout->setContentsMargins( sizeHint().width()/3, 0, sizeHint().width()/3,0);
    this->pActionsLayout->setAlignment(Qt::AlignCenter);

}

void ActionsWidget::onLogout() {
    //apelez cv functie care deconecteaza userul
    //ma intorc la home page
    common::writeRequest(ServerConnection::getInstance().getSocket(), common::ClientRequests::REQUEST_LOGOUT);
    emit loggedOut();

}

void ActionsWidget::onFriendsButton() {
    emit goToFriendsMenu();
}

void ActionsWidget::newPostPopUp() {

}

void ActionsWidget::onMyProfile() {

}

void ActionsWidget::onPost() {

}


void ActionsWidget::onSettings() {

}

void ActionsWidget::onSendMessage() {

}



ActionsWidget::~ActionsWidget()
= default;