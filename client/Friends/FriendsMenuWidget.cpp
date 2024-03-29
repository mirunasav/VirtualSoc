//
// Created by mrnk on 12/14/22.
//

#include <QVBoxLayout>
#include "FriendsMenuWidget.h"
#include "AddFriendsWidget.h"
#include "FriendsList.h"
#include "../LogInInterface/MainWindow.h"
#include "FriendRequestsWidget.h"
#include "BlockedListWidget.h"

FriendsMenuWidget::FriendsMenuWidget(QWidget *pParentWindow)  :
        QWidget(pParentWindow ){
    this->initWidget();
}

void FriendsMenuWidget::initWidget() {
    this->createComponents();
    this->settleLayouts();
    this->styleComponents();


    connect(this->pAddFriendsButton, &QPushButton :: clicked,this, &FriendsMenuWidget::swapWidgetsAddFriends);
    connect(this->pMyFriendsButton, &QPushButton :: clicked,this, &FriendsMenuWidget::swapWidgetsFriendList);
    connect(this->pFriendRequestsButton, &QPushButton :: clicked,this, &FriendsMenuWidget::swapWidgetsFriendRequests);
    connect(this->pBlockedListButton, &QPushButton :: clicked,this, &FriendsMenuWidget::swapWidgetsBlockedList);

}

void FriendsMenuWidget::createComponents() {

    this->pHorizontalSplitter= new QSplitter (Qt::Horizontal);
    this->pVerticalSplitter = new QSplitter (Qt::Vertical);

    this->pFriendsLabel = new QLabel(FriendsMenuWidget ::pFriendsListLabelText, this);
    this->pFriendsLabel->setAlignment(Qt::AlignCenter);

    this->pFriendsLabel->setFont(this->FriendsLabelFont);

    this->pChangeableWidget = new FriendsList(this);
    this->pButtonsWidget = new QWidget(this);

    this->pMainLayout = new QVBoxLayout();
    this->pButtonsLayout = new QVBoxLayout();

    this->pAddFriendsButton = new QPushButton(FriendsMenuWidget::pAddFriendsButtonText, this);
    this->pMyFriendsButton = new QPushButton(FriendsMenuWidget::pMyFriendsButtonText, this);
    this->pFriendRequestsButton = new QPushButton(FriendsMenuWidget::pFriendRequestsButtonText, this);
    this->pBlockedListButton = new QPushButton(FriendsMenuWidget::pBlockedListButtonText, this);
}

void FriendsMenuWidget::settleLayouts() {
    this->setLayout(this->pMainLayout);
    this->pButtonsWidget->setLayout(this->pButtonsLayout);

    this->pMainLayout ->addWidget(this->pHorizontalSplitter);
    this->pMainLayout ->addWidget(this->pVerticalSplitter);

    this->pHorizontalSplitter ->addWidget(this->pButtonsWidget);
    this->pHorizontalSplitter->addWidget(this->pChangeableWidget);

    this->pVerticalSplitter ->addWidget(this->pFriendsLabel);
    this->pVerticalSplitter ->addWidget(this->pHorizontalSplitter);


    this->pButtonsLayout ->addWidget(this->pMyFriendsButton);
    this->pButtonsLayout ->addWidget(this->pAddFriendsButton);
    this->pButtonsLayout ->addWidget(this->pFriendRequestsButton);
    this->pButtonsLayout ->addWidget(this->pBlockedListButton);

    this->pButtonsLayout->setContentsMargins( 0, MainWindow::HEIGHT/3,0,MainWindow::HEIGHT/2.5);
}

void FriendsMenuWidget::styleComponents() {
    this->pHorizontalSplitter->setSizes(QList <int>{sizeHint().width()*1/3, sizeHint().width()*7/3*5});
    this->pVerticalSplitter->setSizes(QList <int>{sizeHint().height()*1/3, sizeHint().height()*7/3*5});

}

void FriendsMenuWidget::swapWidgetsAddFriends() {
    QWidget *pOldWidget = this->pChangeableWidget;

    this->pChangeableWidget = new AddFriendsWidget(this);

    this->pHorizontalSplitter->replaceWidget(1, this->pChangeableWidget);

    this->pFriendsLabel->setText(FriendsMenuWidget::pFriendsAddFriendsLabelText);

    pOldWidget->hide();
    delete pOldWidget;
}

void FriendsMenuWidget::swapWidgetsFriendList() {
    QWidget *pOldWidget = this->pChangeableWidget;

    this->pChangeableWidget = new FriendsList(this);

    this->pHorizontalSplitter->replaceWidget(1, this->pChangeableWidget);

    this->pFriendsLabel->setText(FriendsMenuWidget::pFriendsListLabelText);
    pOldWidget->hide();
    delete pOldWidget;

}

void FriendsMenuWidget::swapWidgetsFriendRequests() {
    QWidget *pOldWidget = this->pChangeableWidget;

    this->pChangeableWidget = new FriendRequestsWidget(this);

    this->pHorizontalSplitter->replaceWidget(1, this->pChangeableWidget);
    this->pFriendsLabel->setText(FriendsMenuWidget::pFriendRequestsButtonText);

    pOldWidget->hide();
    delete pOldWidget;
}

void FriendsMenuWidget::swapWidgetsBlockedList() {
    QWidget *pOldWidget = this->pChangeableWidget;

    this->pChangeableWidget = new BlockedListWidget(this);//new blocked list

    this->pHorizontalSplitter->replaceWidget(1, this->pChangeableWidget);
    this->pFriendsLabel->setText(FriendsMenuWidget::pBlockedListLabelText);

    pOldWidget->hide();
    delete pOldWidget;
}


