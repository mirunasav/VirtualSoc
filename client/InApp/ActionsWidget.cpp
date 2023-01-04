//
// Created by mrnk on 12/2/22.
//

#include <QVBoxLayout>
#include <QMenuBar>
#include "ActionsWidget.h"
#include "../LogInInterface/MainWindow.h"
#include "../ServerConnection.h"
ActionsWidget:: ActionsWidget(QWidget *pParentWindow) : QWidget(pParentWindow)
{
    this->initWidget();
}

void ActionsWidget::initWidget()
{
    this->createComponents();
    this->settleLayouts();
    this->adjustLayouts();

   this->connectComponents();
}

void ActionsWidget::createComponents() {

    this->pActionsLayout = new QVBoxLayout(this);

    this->pMyFeedButton = new QPushButton(ActionsWidget::pMyFeedButtonText, this);
    this->pPostButton = new QPushButton(ActionsWidget::pPostButtonText, this);
    this->pFriendsButton = new QPushButton(ActionsWidget::pFriendsButtonText, this);
    this->pMessagesButton = new QPushButton(ActionsWidget::pMessagesButtonText, this);
    this->pSettingsButton = new QPushButton(ActionsWidget::pSettingsButtonText, this);
    this->pLogoutButton = new QPushButton(ActionsWidget:: pLogoutButtonText, this);
}

void ActionsWidget::settleLayouts() {
    this->pActionsLayout->addWidget(this->pMyFeedButton);
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
void ActionsWidget::connectComponents() {
    connect(this->pLogoutButton, &QPushButton ::clicked, this, &ActionsWidget::onLogout);
    connect(this, SIGNAL(loggedOut()), this->parent(), SLOT(swapWidgetsLogOut()));

    connect(this->pFriendsButton, &QPushButton ::clicked, this, &ActionsWidget::onFriendsButton);
    connect(this, SIGNAL(goToFriendsMenu()), this->parent(), SLOT(swapWidgetsFriendsMenu()));

    connect(this->pSettingsButton, &QPushButton ::clicked, this, &ActionsWidget::onSettings);
    connect(this, SIGNAL(goToSettings()), this->parent(), SLOT(swapWidgetsSettings()));


    connect(this->pMessagesButton, &QPushButton ::clicked, this, &ActionsWidget::onSendMessage);
    connect(this, SIGNAL(goToMessages()), this->parent(), SLOT(swapWidgetsMessages() ));

    connect(this->pMyFeedButton, &QPushButton ::clicked, this, &ActionsWidget::onMyFeedButton);
    connect(this, SIGNAL(goToMyFeed()), this->parent(),SLOT(swapWidgetsMyFeed()));

    connect(this->pPostButton, &QPushButton ::clicked, this, &ActionsWidget::onPost);
    connect(this, SIGNAL(goToNewPost()), this->parent(),SLOT(swapWidgetsNewPost()));
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
    emit goToNewPost();
}


void ActionsWidget::onSettings() {
    emit goToSettings();
}

void ActionsWidget::onSendMessage() {
    emit goToMessages();
}

void ActionsWidget::onMyFeedButton() {
    emit goToMyFeed();
}


ActionsWidget::~ActionsWidget()
= default;