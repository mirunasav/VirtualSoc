//
// Created by mrnk on 12/26/22.
//

#include <QVBoxLayout>
#include "NewMessageWidget.h"
#include "../ServerConnection.h"

NewMessageWidget::NewMessageWidget(QWidget *pParent) : QWidget(pParent){
    this->initWidget();
}

void NewMessageWidget::initWidget() {
    this->createComponents();
    this->settleLayouts();
}

void NewMessageWidget::createComponents() {
    this->createListWidget();
    this->pMainLayout = new QVBoxLayout (this);

    this->pButtonLayout = new QVBoxLayout();

    this->pSendMessageButton = new QPushButton(NewMessageWidget::pSendMessageButtonText,this);

    connect(this->pFriendList, SIGNAL(itemClicked(QListWidgetItem *)),this, SLOT(highlightChecked(QListWidgetItem *)));
    connect(this->pSendMessageButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(this, SIGNAL(sendMessage(std::string &)), this->parent(), SLOT(swapWidgetsSendMessage(std::string &)));

}

void NewMessageWidget::createListWidget() {
    this->pFriendList = new QListWidget;
    QStringList friendList;

    this->acquireFriendList(friendList);

    this->pFriendList->addItems(friendList);

    QListWidgetItem * item = nullptr;
    for(int i = 0; i < this->pFriendList->count(); ++i)
    {
        item = this->pFriendList->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
    }

    this->pFriendList->setStyleSheet(
            "QListWidget {"
            "background-color:#263440;"
            "font : 25px;"
            "}"
            "QListWidget :: indicator  {"
            "border : 1px solid white;"
            "}"
            );


}

void NewMessageWidget::settleLayouts() {
    this->setLayout(this->pMainLayout);

    this->pMainLayout->addWidget(this->pFriendList);
    this->pMainLayout->addItem(this->pButtonLayout);

    this->pButtonLayout->addWidget(this->pSendMessageButton);
    this->pButtonLayout->setAlignment(Qt::AlignCenter);
    //this->pMainLayout->setAlignment(this->pFriendList, Qt::AlignCenter);
}

void NewMessageWidget::highlightChecked(QListWidgetItem *item) {
    if(item->checkState() == Qt::Unchecked)
    {
        item->setCheckState(Qt::Checked);
        item->setBackground(QColor("#6666ff"));
    }
    else
    {
        item->setCheckState(Qt::Unchecked);
        item->setBackground(QColor("#263440"));
    }
    /*if(item->checkState() == Qt::Checked)
        item->setBackground(QColor("#6666ff"));
    else
        item->setBackground(QColor("#4d4d4d"));*/

}

void NewMessageWidget::sendMessage() {

    std::string selectedUsernames;
    for(int i = 0; i < this->pFriendList->count(); ++i)
    {
        if(this->pFriendList->item(i)->checkState() == Qt::Checked) {
            selectedUsernames.append(this->pFriendList->item(i)->text().toStdString());
            selectedUsernames.append("|");
        }
    }
     emit  sendMessage(selectedUsernames);

}

void NewMessageWidget::acquireFriendList(QStringList& friendList) {
    try {
        int numberOfFriends;
        common::writeRequest(ServerConnection::getInstance().getSocket(),common::ClientRequests::REQUEST_GET_NUMBER_OF_FRIENDS);
        common::readBufferInt(ServerConnection::getInstance().getSocket(), numberOfFriends);

        common::writeRequest(ServerConnection::getInstance().getSocket(), common::ClientRequests::REQUEST_GET_FRIEND_LIST);

        // int numberOfFriends = readBufferInt(ServerConnection::getInstance().getSocket(),numberOfFriends );

        std::string username, typeOfFriendship;

        for(int i = 1; i<=numberOfFriends; i++)
        {
            username = common::readString(ServerConnection::getInstance().getSocket());
            typeOfFriendship = common::readString(ServerConnection::getInstance().getSocket());

            friendList << username.c_str();
        }

    }
    catch ( std::exception const & ex ) //daca e vreo exceptie, ne reconectam
    {
        ServerConnection::getInstance().connect(common::SERVER_IP, common::SERVER_PORT);
    }

}

