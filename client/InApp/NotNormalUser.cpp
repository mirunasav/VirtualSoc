//
// Created by mrnk on 12/4/22.
//

#include <QHBoxLayout>
#include "NotNormalUser.h"
#include "../Posts/FeedWidget.h"
#include "../LogInInterface/MainWindow.h"
#include "../ServerConnection.h"

NotNormalUser::NotNormalUser(QWidget *pParentWindow, bool isAdmin):
        QWidget ( pParentWindow ){
    this->isAdmin = isAdmin;
    this->initWidget();
}

void NotNormalUser::initWidget() {
    this->createComponents();
    this->settleLayouts();
    this->styleComponents();

    connect(this->pReturnToStartPage, &QPushButton :: clicked, [this] {
        this->onReturn();
    });
    connect(this, SIGNAL(returned()), this, SLOT(swapWidgetsReturn()));
    connect(this->pRefreshFeedButton, SIGNAL(clicked()), this, SLOT(onRefresh()));
    connect(this, SIGNAL(refreshed()), this, SLOT(swapWidgetsRefreshFeed()));

}
void NotNormalUser::createComponents() {
    this->pCentralWidget = new QWidget(this);

    this->pLayout = new QHBoxLayout();
    this->pMainLayout = new QHBoxLayout();

    this->pButtonLayout = new QVBoxLayout(this->pButtonWidget);

    this->pButtonLayout->setAlignment(this->pButtonWidget, Qt::AlignBottom);

    if(!this->isAdmin)
        this->pFeedWidget = new FeedWidget(this,false);
    else
        this->pFeedWidget = new FeedWidget(this,true);

    this->pButtonWidget = new QWidget(this);

    this->pReturnToStartPage = new QPushButton(NotNormalUser::pReturnButtonText , this);
    this->pRefreshFeedButton = new QPushButton(NotNormalUser::pRefreshFeedButtonText , this);


    this->pSplitter = new QSplitter(Qt::Horizontal);

    this->pButtonLayout->setContentsMargins( sizeHint().width()/3, 0, sizeHint().width()/3,0);
    this->pButtonLayout->setAlignment(Qt::AlignCenter);
}

void NotNormalUser::settleLayouts() {
    this->setLayout(this->pLayout);

    this->pLayout->addWidget(this->pCentralWidget);
    this->pCentralWidget->setLayout(this->pMainLayout);

    this->pMainLayout->addWidget(this->pSplitter);

    this->pSplitter->addWidget(this->pButtonWidget);
    this->pSplitter->addWidget(this->pFeedWidget);

    this->pButtonWidget->setLayout(pButtonLayout);

    this->pButtonLayout->addWidget(this->pReturnToStartPage);
    this->pButtonLayout ->addWidget(this->pRefreshFeedButton);


}


void NotNormalUser::styleComponents() {

    this->pSplitter->setSizes(QList <int>{sizeHint().width()*1/3, sizeHint().width()*2/3*5});

}

void NotNormalUser::swapWidgetsReturn() {
    QWidget* pOldWidget = this->pCentralWidget;
    this->pCentralWidget = new MainWindow(nullptr);

    ServerConnection::getInstance().disconnect();

    this->pLayout->removeWidget(pOldWidget);
    pLayout->addWidget(pCentralWidget);

    pOldWidget->hide();
    delete pOldWidget;
}

void NotNormalUser::onReturn() {
    emit this->returned();

}

void NotNormalUser::swapWidgetsRefreshFeed() {
    QWidget* pOldWidget = this->pFeedWidget;

    if(!this->isAdmin)
        this->pFeedWidget = new FeedWidget(this, false);
    else
        this->pFeedWidget = new FeedWidget(this, true);

    this->pSplitter->replaceWidget(1, this->pFeedWidget);

    pOldWidget->hide();
    delete pOldWidget;
}

void NotNormalUser::onRefresh() {
    emit refreshed();
}
