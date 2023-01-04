//
// Created by mrnk on 12/2/22.
//

#include <QVBoxLayout>
#include "FeedWidget.h"
#include "../../common/common.h"
#include "../ServerConnection.h"
#include "PostWidget.h"
#include "../MainWindow.h"
#include <QTimer>
#include <QScrollBar>
#include <iostream>

FeedWidget:: FeedWidget(QWidget *pParentWindow, bool loggedIn):
        QWidget(pParentWindow){
    this->loggedIn = loggedIn;
    this->initWidget();

}
void FeedWidget::initWidget()
{
   createComponents();
   settleLayouts();
   this->refreshFeed();
}
void FeedWidget::createComponents()
{
    this->pLayout = new QVBoxLayout(this);
    this->pPostsLayout = new QVBoxLayout();

    this->pPostsList = new QListWidget(this);

}
void FeedWidget::settleLayouts()
{
    this->setLayout(this->pLayout);

    this->pLayout ->addItem(this->pPostsLayout);
    this->pPostsLayout->addWidget(this->pPostsList);
    this->pLayout->setContentsMargins(MainWindow::WIDTH/10, MainWindow::HEIGHT/10,MainWindow::WIDTH/10, MainWindow::HEIGHT/10);

}

void FeedWidget::acquireFeed() {
    try {
        if(this->loggedIn)
            common::writeRequest(ServerConnection::getInstance().getSocket(), common::ClientRequests::REQUEST_LOAD_FEED);
        else
            common::writeRequest(ServerConnection::getInstance().getSocket(),common::ClientRequests::REQUEST_LOAD_FEED_NOT_LOGGED_IN);


        std::string username, textOfPost, visibleToWhom, dateOfPost, isOwnerOfPost;
        int postID;

        int numberOfPostsFromServer = 0;
        common::readBufferInt(ServerConnection::getInstance().getSocket(), numberOfPostsFromServer);

        for(int i = 0; i<numberOfPostsFromServer ; i++)
        {
            isOwnerOfPost = common::readString(ServerConnection::getInstance().getSocket());
            username = common::readString(ServerConnection::getInstance().getSocket());
            textOfPost = common::readString(ServerConnection::getInstance().getSocket());
            visibleToWhom = common::readString(ServerConnection::getInstance().getSocket());
            dateOfPost = common::readString(ServerConnection::getInstance().getSocket());
            postID = stoi(common::readString(ServerConnection::getInstance().getSocket()));
            this->addToFeed(postID,isOwnerOfPost,  username, textOfPost, visibleToWhom, dateOfPost);
        }

    }
    catch(std::exception const & ex )
    {
        ServerConnection::getInstance().connect(common::SERVER_IP, common::SERVER_PORT);
    }
}


void FeedWidget::addToFeed(int ID,const std::string& isOwnerOfPost, const std::string& username, const std::string& textOfPost, const std::string& visibleToWhom, const std::string& dateOfPost) {
    //chestia aia cu pitem si sa fac de fiecare data new postWidget

    auto *pItem = new QListWidgetItem(this->pPostsList);//intermediar

    auto *pWidget = new PostWidget(this,ID,isOwnerOfPost, username, textOfPost, visibleToWhom, dateOfPost);

    pWidget->setStyleSheet( "QLabel {"
                            "background-color: #f1f0b1;"
                            "border-style: hidden;"
                            "border-radius: 8px;"
                            "border-width: 1px;"
                            "padding: 3px;"
                            "color :  #1d1817; "
                            "}");
    pItem->setSizeHint( pWidget->minimumSizeHint() );

    pItem->setFlags( pItem->flags() & ~ ( Qt::ItemIsEnabled ) );

    this->pPostsList->addItem( pItem );  /// adaugam intermediarul in lista
    this->pPostsList->setItemWidget( pItem, pWidget );///asociem intermediarul cu widgetul

    connect(pWidget, SIGNAL(remove(int)), this, SLOT(removePost(int)));
}

void FeedWidget::refreshFeed() {
    this->clearFeed();
    this->acquireFeed();
}

void FeedWidget::clearFeed() {

    if(this->pPostsList->count() > 0)
    {
        for ( int i = this->pPostsList->count() - 1; i>=0 ; i-- ) {
            auto * pItem = this->pPostsList->item ( i ); // obtinem din lista intermediar-ul
            auto * pMessage = this->pPostsList->itemWidget( pItem ); // din intermediar, obtinem obiectul

            this->pPostsList->removeItemWidget( pItem ); // scoatem intermediarul, va scoate si obiectul

            delete pItem; // stergem intermediarul
            delete pMessage; // stergem obiectul
        }
    }

}

void FeedWidget::removePost(int postID) {
    //scriu request
    common::writeRequest(ServerConnection::getInstance().getSocket(), common::ClientRequests::REQUEST_REMOVE_POST);
    common::writeRequestNumber(ServerConnection::getInstance().getSocket(),postID);

    this->refreshFeed();
}
