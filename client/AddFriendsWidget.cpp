//
// Created by mrnk on 12/19/22.
//

#include <QVBoxLayout>
#include <QMessageBox>
#include "ServerConnection.h"
#include "MainWindow.h"
#include "AddFriendsWidget.h"

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

    this->pSendRequestLayout->setAlignment(Qt::AlignCenter);
    this->pSendRequestLayout->setContentsMargins(MainWindow::WIDTH / 10, 0, MainWindow::WIDTH / 10, 0);
    this->pUsernameLineEdit->setMaximumWidth(300);
    this->pLineEditLayout->setAlignment(this->pUsernameLineEdit, Qt::AlignCenter);


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

    common::writeRequest(ServerConnection::getInstance().getSocket(), common::ClientRequests::REQUEST_ADD_FRIEND);
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
    }
}
void AddFriendsWidget::notificationPopUp(const char *message) {
    //apare un text box pop up; parintele este this
    //titlul este ..., mesajul este message, un buton de ok
    QMessageBox::information(this, " ", message,QMessageBox::Ok);

}

