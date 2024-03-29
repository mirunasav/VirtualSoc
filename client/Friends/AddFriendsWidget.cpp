//
// Created by mrnk on 12/19/22.
//

#include <QVBoxLayout>
#include <QMessageBox>
#include "../ServerConnection.h"
#include "../LogInInterface/MainWindow.h"
#include "AddFriendsWidget.h"
#include <QKeyEvent>
#include <QKeyEvent>
AddFriendsWidget::AddFriendsWidget(QWidget *pParentWindow) :
                QWidget (pParentWindow) {
    this->initWidget();
}

void AddFriendsWidget::initWidget() {

    this->createComponents();
    this->settleLayouts();

    connect(this->pSendRequestButton, &QPushButton :: clicked,this, &AddFriendsWidget::onSendRequest);

}

void AddFriendsWidget::createComponents() {

    this->pMainLayout = new QHBoxLayout(this);
    this->pButtonLayout = new QHBoxLayout(nullptr);
    this->pSendRequestLayout = new QVBoxLayout (nullptr);
    this->pLineEditLayout = new QHBoxLayout(nullptr);

    this->pUsernameLineEdit = new QLineEdit(this);
    this->pSearchUsernameLabel = new QLabel (AddFriendsWidget :: pSearchUserText, this);

    this->pSendRequestButton = new QPushButton (AddFriendsWidget :: pSendRequestButtonText, this);

    this->pMainLayout->setAlignment(Qt::AlignCenter);
    this->pButtonLayout->setAlignment(Qt::AlignRight);

    this->pSendRequestLayout->setAlignment(this->pLineEditLayout,Qt::AlignCenter);
    this->pSendRequestLayout->setContentsMargins(MainWindow::WIDTH / 10, 0, MainWindow::WIDTH / 10, 0);
    this->pLineEditLayout->setAlignment(this->pSearchUsernameLabel, Qt::AlignLeft);


}

void AddFriendsWidget::settleLayouts() {

    this->pMainLayout->addItem(this->pSendRequestLayout);

    this->pSendRequestLayout->addItem(this->pLineEditLayout);
    this->pSendRequestLayout->addItem(this->pButtonLayout);

    this->pLineEditLayout->addWidget(this->pSearchUsernameLabel);
    this->pLineEditLayout->addWidget(this->pUsernameLineEdit);

    this->pButtonLayout->addWidget(this->pSendRequestButton);

}

void AddFriendsWidget::onSendRequest() {
    ServerConnection::getInstance().connect(common::SERVER_IP, common::SERVER_PORT);

    if (!ServerConnection::getInstance().isConnected()) //nu a mers conexiunea
    {
        this->notificationPopUp(LoginWidget::pServerDown);
        return;
    }
    std::string username = this->pUsernameLineEdit->text().toStdString();

    common::writeRequest(ServerConnection::getInstance().getSocket(), common::ClientRequests::REQUEST_SEND_FRIEND_REQUEST);
    common::writeString(ServerConnection::getInstance().getSocket(),username);

    common::ServerResponse response = common ::readResponse(ServerConnection::getInstance().getSocket());

    switch(response)
    {
        case common::ServerResponse::ADD_FRIENDS_INVALID_USER:
            this->notificationPopUp(AddFriendsWidget::pInvalidUserText);
            break;
        case common::ServerResponse::ADD_FRIENDS_OWN_USERNAME:
            this->notificationPopUp(AddFriendsWidget::pOwnUsername);
            break;
        case common::ServerResponse:: ADD_FRIENDS_REQUEST_SENT:
            this->notificationPopUp(AddFriendsWidget::pRequestSentText);
            break;
        case common::ServerResponse::ADD_FRIENDS_ALREADY_FRIEND:
            this->notificationPopUp(AddFriendsWidget::pUserAlreadyFriend);
            break;
        case common::ServerResponse::ADD_FRIENDS_REQUEST_ALREADY_SENT:
            this->notificationPopUp(AddFriendsWidget::pRequestAlreadySent);
            break;
        case common::ServerResponse::ADD_FRIENDS_USER_BLOCKED_YOU:
            this->notificationPopUp(AddFriendsWidget::pUserBlockedYou);
            break;
        case common::ServerResponse::ADD_FRIENDS_USER_BLOCKED:
            this->notificationPopUp(AddFriendsWidget::pUserBlockedByYou);
            break;
    }
    this->pUsernameLineEdit->clear();
}
void AddFriendsWidget::notificationPopUp(const char *message) {
    //apare un text box pop up; parintele este this
    //titlul este ..., mesajul este message, un buton de ok
    QMessageBox::information(this, " ", message,QMessageBox::Ok);

}

void AddFriendsWidget::keyPressEvent(QKeyEvent *event) {
    if( event ->key() == Qt::Key_Return || event ->key() == Qt::Key_Enter)
    {
        this->onSendRequest();
    }
}

