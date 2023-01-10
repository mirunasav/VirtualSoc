//
// Created by mrnk on 1/7/23.
//

#include <QVBoxLayout>
#include "FriendRequestsWidget.h"
#include "../ServerConnection.h"
#include "RequestItem.h"


FriendRequestsWidget::FriendRequestsWidget(QWidget *pParent):
QWidget(pParent){
    this->initWidget();
}

void FriendRequestsWidget::initWidget() {
    this->createComponents();
    this->settleLayouts();

    this->refreshRequestsList();
}

void FriendRequestsWidget::createComponents() {
    this->pMainLayout = new QVBoxLayout(this);
    this->pFriendRequestsLayout = new QVBoxLayout();

    this->pFriendRequestsList = new QListWidget (this);
}

void FriendRequestsWidget::settleLayouts() {
    this->setLayout (this->pMainLayout);

    this->pMainLayout ->addItem(this->pFriendRequestsLayout);
    this->pFriendRequestsLayout->addWidget(this->pFriendRequestsList);

    this->pFriendRequestsLayout->setAlignment(Qt::AlignLeft);
}

void FriendRequestsWidget::refreshRequestsList() {
    this->clearList();
    this->acquireRequestsList();

}
void FriendRequestsWidget::acquireRequestsList() {
    try
    {
        common::writeRequest(ServerConnection::getInstance().getSocket(), common::ClientRequests::REQUEST_GET_REQUESTS_LIST);

        int numberOfRequests = 0;
        common::readBufferInt(ServerConnection::getInstance().getSocket(), numberOfRequests);
        std::string username;

        for(int i = 1; i<= numberOfRequests ; i++)
        {
            username  = common::readString(ServerConnection::getInstance().getSocket());
            this->addRequestToList(username);
        }

    }
    catch ( std::exception const & ex ) //daca e vreo exceptie, ne reconectam
    {
        ServerConnection::getInstance().connect(common::SERVER_IP, common::SERVER_PORT);
    }

}

void FriendRequestsWidget::addRequestToList(const std::string &username) {
    auto *pItem = new QListWidgetItem(this->pFriendRequestsList);//intermediar

    auto *pWidget = new RequestItem(this,username);

    pItem->setSizeHint( pWidget->minimumSizeHint() );

    pItem->setFlags( pItem->flags() & ~ ( Qt::ItemIsEnabled ) );

    this->pFriendRequestsList->addItem( pItem );  /// adaugam intermediarul in lista
    this->pFriendRequestsList->setItemWidget( pItem, pWidget );///asociem intermediarul cu widgetul

    //signal : accept si deny
    connect(pWidget, SIGNAL(accept(const std::string &)), this, SLOT(acceptRequest(const std::string &)));
    connect(pWidget, SIGNAL(deny(const std::string &)), this, SLOT(denyRequest(const std::string &)));
    connect(pWidget, SIGNAL(block(const std::string &)), this, SLOT(blockUser(const std::string &)));
}

void FriendRequestsWidget::clearList() {
    int count = this->pFriendRequestsList->count()-1;
    for (int i = count; i>=0; i--)
    {
        auto *pItem = this->pFriendRequestsList->item(i);//intermediar
        auto *pRequest = this->pFriendRequestsList->itemWidget(pItem);//obiect

        this->pFriendRequestsList->removeItemWidget(pItem);

        delete pItem;
        delete pRequest;
    }
}

void FriendRequestsWidget::acceptRequest(const std::string &usernameAdded) {
    common::writeRequest(ServerConnection::getInstance().getSocket(),common::ClientRequests::REQUEST_ADD_FRIEND);
    common::writeString(ServerConnection::getInstance().getSocket(),usernameAdded);
    this->refreshRequestsList();
}

void FriendRequestsWidget::denyRequest(const std::string &usernameDenied) {
    common::writeRequest(ServerConnection::getInstance().getSocket(),common::ClientRequests::REQUEST_DENY_REQUEST);
    common::writeString(ServerConnection::getInstance().getSocket(),usernameDenied);
    this->refreshRequestsList();
}

void FriendRequestsWidget::blockUser(const std::string &usernameToBlock) {
    common::writeRequest(ServerConnection::getInstance().getSocket(),common::ClientRequests::REQUEST_BLOCK_USER);
    common::writeString(ServerConnection::getInstance().getSocket(),usernameToBlock);
    this->refreshRequestsList();
}

