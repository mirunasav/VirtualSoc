//
// Created by mrnk on 12/23/22.
//

#include <QVBoxLayout>
#include "FriendsList.h"
#include "../ServerConnection.h"
#include "../../common/common.h"
#include "FriendItem.h"
#include <QTimer>

using namespace common;

class write;

FriendsList::FriendsList(QWidget *pParentWidget) : QWidget(pParentWidget){
    this->numberOfFriendsCounter = 0;
    this->initWidget();
}

void FriendsList::initWidget() {
    this->createComponents();
    this->settleLayouts();

   this->refreshFriendList();

}

void FriendsList::createComponents() {
    this->pMainLayout = new QVBoxLayout (this);
    this->pNumberOfFriendsLayout = new QHBoxLayout (nullptr);
    this->pFriendListLayout = new QVBoxLayout(nullptr);

    this->pNumberOfFriendsLabel = new QLabel (FriendsList::pNumberOfFriendsText,this);
    //luam numarul de prieteni pt a putea initializa

    this->refreshNumberOfFriendsCounter();
    this->pFriendsCounter = new QLabel (std::to_string(this->numberOfFriendsCounter).c_str(),this);

    this->pFriends = new QListWidget (this);

  //  this->pRefreshListTimer = new QTimer (this);


}

void FriendsList::settleLayouts() {
    this->setLayout(this->pMainLayout);

    this->pMainLayout->addItem (this->pNumberOfFriendsLayout);
    this->pMainLayout->addItem (this->pFriendListLayout);

    this->pNumberOfFriendsLayout->addWidget(this->pNumberOfFriendsLabel);
    this->pNumberOfFriendsLayout->addWidget(this->pFriendsCounter);

    this->pFriendListLayout->addWidget(this->pFriends);
    this->pFriendListLayout->setAlignment(Qt::AlignLeft);

    this->pNumberOfFriendsLayout->setAlignment(this->pFriendsCounter, Qt::AlignLeft);

    //connect(this->pRefreshListTimer, SIGNAL(timeout()), this, SLOT(refreshFriendList()));
}
void FriendsList::acquireFriendList() {
    try {
       writeRequest(ServerConnection::getInstance().getSocket(), ClientRequests::REQUEST_GET_FRIEND_LIST);

       // int numberOfFriends = readBufferInt(ServerConnection::getInstance().getSocket(),numberOfFriends );

        std::string username, typeOfFriendship;
        for(int i = 1; i<=this->numberOfFriendsCounter; i++)
        {
           username = readString(ServerConnection::getInstance().getSocket());
           typeOfFriendship = readString(ServerConnection::getInstance().getSocket());

            this->addFriendToList(username, typeOfFriendship);
        }

    }
    catch ( std::exception const & ex ) //daca e vreo exceptie, ne reconectam
    {
        ServerConnection::getInstance().connect(common::SERVER_IP, common::SERVER_PORT);
    }

}

void FriendsList::addFriendToList(const std::string & username, const std::string & typeOfFriendship) {

    auto *pItem = new QListWidgetItem(this->pFriends);//intermediar

    auto *pWidget = new FriendItem(this, username, typeOfFriendship);

    pItem->setSizeHint( pWidget->minimumSizeHint() );

    pItem->setFlags( pItem->flags() & ~ ( Qt::ItemIsEnabled ) );

    this->pFriends->addItem( pItem );  /// adaugam intermediarul in lista
    this->pFriends->setItemWidget( pItem, pWidget );///asociem intermediarul cu widgetul

    connect(pWidget, SIGNAL(remove(const std::string &)), this, SLOT(removeFriend(const std::string &)));
    connect(pWidget, SIGNAL(changeType(const std::string &,const std::string &)), this, SLOT(changeFriendshipType(const std::string &, const std::string &)));
}



void FriendsList::refreshFriendList()  {
 //   this->pRefreshListTimer->stop();

    this->clearFriendList();
    this->refreshNumberOfFriendsCounter();
    this->acquireFriendList();

  //  this->restartTimer();
}

void FriendsList::clearFriendList() {

    int count = this->pFriends->count()-1;
    for (int i = count; i>=0; i--)
    {
        auto *pItem = this->pFriends->item(i);//intermediar
        auto *pFriend = this->pFriends->itemWidget(pItem);//obiect

        this->pFriends->removeItemWidget(pItem);

        delete pItem;
        delete pFriend;
    }
}

void FriendsList::refreshNumberOfFriendsCounter() {
    common::writeRequest(ServerConnection::getInstance().getSocket(),ClientRequests::REQUEST_GET_NUMBER_OF_FRIENDS);
    common::readBufferInt(ServerConnection::getInstance().getSocket(), this->numberOfFriendsCounter);
}

void FriendsList::removeFriend(const std::string & usernameToRemove) {
    common::writeRequest(ServerConnection::getInstance().getSocket(),ClientRequests::REQUEST_REMOVE_FRIEND);
    common::writeString(ServerConnection::getInstance().getSocket(), usernameToRemove);
    this->refreshFriendList();
}

void FriendsList::changeFriendshipType(const std::string & username, const std::string &newFriendshipType) {
   // this->pRefreshListTimer->stop();

    common::writeRequest(ServerConnection::getInstance().getSocket(),ClientRequests::REQUEST_CHANGE_TYPE);
    common::writeString(ServerConnection::getInstance().getSocket(), username);
    common::writeString(ServerConnection::getInstance().getSocket(), newFriendshipType);


}

