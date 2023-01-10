//
// Created by mrnk on 1/10/23.
//

#include <QVBoxLayout>
#include "BlockedListWidget.h"
#include "../../common/common.h"
#include "../ServerConnection.h"
#include "BlockedItem.h"

BlockedListWidget::BlockedListWidget(QWidget *pParent) : QWidget(pParent){
    this->initWidget();
}

void BlockedListWidget::initWidget() {
    this->createComponents();
    this->settleLayouts();
    this->refreshBlockedList();
}

void BlockedListWidget::createComponents() {
    this->pMainLayout = new QVBoxLayout(this);
    this->pBlockedListLayout = new QVBoxLayout();
    this->pBlockedListWidget = new QListWidget (this);
}

void BlockedListWidget::settleLayouts() {
    this->setLayout (this->pMainLayout);

    this->pMainLayout ->addItem(this->pBlockedListLayout);
    this->pBlockedListLayout->addWidget(this->pBlockedListWidget);

    this->pBlockedListLayout->setAlignment(Qt::AlignLeft);
}

void BlockedListWidget::addItemToList(const std::string & username){
    auto *pItem = new QListWidgetItem(this->pBlockedListWidget);//intermediar

    auto *pWidget = new BlockedItem(this,username);

    pItem->setSizeHint( pWidget->minimumSizeHint() );

    pItem->setFlags( pItem->flags() & ~ ( Qt::ItemIsEnabled ) );

    this->pBlockedListWidget->addItem( pItem );  /// adaugam intermediarul in lista
    this->pBlockedListWidget->setItemWidget( pItem, pWidget );///asociem intermediarul cu widgetul

    connect(pWidget, SIGNAL(unblock(const std::string &)), this, SLOT(unblock(const std::string &)));
}

void BlockedListWidget::clearList() {
    int count = this->pBlockedListWidget->count()-1;
    for (int i = count; i>=0; i--)
    {
        auto *pItem = this->pBlockedListWidget->item(i);//intermediar
        auto *pRequest = this->pBlockedListWidget->itemWidget(pItem);//obiect

        this->pBlockedListWidget->removeItemWidget(pItem);

        delete pItem;
        delete pRequest;
    }
}

void BlockedListWidget::refreshBlockedList() {
    this->clearList();
    this->acquireBlockedList();
}

void BlockedListWidget::acquireBlockedList() {
    //scriu request get blocked list
    try
    {
        common::writeRequest(ServerConnection::getInstance().getSocket(), common::ClientRequests::REQUEST_GET_BLOCKED_LIST);

        int numberOfBLockedUsers= 0;
        common::readBufferInt(ServerConnection::getInstance().getSocket(), numberOfBLockedUsers);
        std::string username;

        for(int i = 1; i<= numberOfBLockedUsers ; i++)
        {
            username  = common::readString(ServerConnection::getInstance().getSocket());
            this->addItemToList(username);
        }

    }
    catch ( std::exception const & ex ) //daca e vreo exceptie, ne reconectam
    {
        ServerConnection::getInstance().connect(common::SERVER_IP, common::SERVER_PORT);
    }
}

void BlockedListWidget::unblock(const std::string &usernameToUnblock) {
    common::writeRequest(ServerConnection::getInstance().getSocket(),common::ClientRequests::REQUEST_UNBLOCK_USER);
    common::writeString(ServerConnection::getInstance().getSocket(),usernameToUnblock);
    this->refreshBlockedList();
}
