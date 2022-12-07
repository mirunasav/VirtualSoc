//
// Created by mrnk on 12/4/22.
//

#include <QHBoxLayout>
#include "NotLoggedIn.h"
#include "client/FeedWidget.h"
#include "client/ActionsWidget.h"
#include "client/MainWindow.h"

NotLoggedIn::NotLoggedIn(QWidget *pParentWindow):
        QWidget ( pParentWindow ){
    this->initWidget();
}

void NotLoggedIn::initWidget() {
    this->createComponents();
    this->settleLayouts();
    this->styleComponents();

    connect(this->pReturnToStartPage, &QPushButton :: clicked, [this] {
        this->onReturn();
    });
    connect(this, SIGNAL(returned()), this, SLOT(swapWidgetsReturn()));

}
void NotLoggedIn::createComponents() {
    this->pCentralWidget = new QWidget(this);

    this->pLayout = new QHBoxLayout();
    this->pMainLayout = new QHBoxLayout();

    this->pButtonLayout = new QVBoxLayout(this->pButtonWidget);

    this->pButtonLayout->setAlignment(this->pButtonWidget, Qt::AlignBottom);

    this->pFeedWidget = new FeedWidget(this);
    this->pButtonWidget = new QWidget(this);

    this->pReturnToStartPage = new QPushButton(NotLoggedIn::pReturnButtonText , this);

    this->pSplitter = new QSplitter(Qt::Horizontal);

}

void NotLoggedIn::settleLayouts() {
    this->setLayout(this->pLayout);

    this->pLayout->addWidget(this->pCentralWidget);
    this->pCentralWidget->setLayout(this->pMainLayout);

    this->pMainLayout->addWidget(this->pSplitter);

    this->pSplitter->addWidget(this->pButtonWidget);
    this->pSplitter->addWidget(this->pFeedWidget);

    this->pButtonWidget->setLayout(pButtonLayout);

    this->pButtonLayout->addWidget(this->pReturnToStartPage);


}


void NotLoggedIn::styleComponents() {

    this->pSplitter->setSizes(QList <int>{sizeHint().width()*1/3, sizeHint().width()*2/3*5});

}

void NotLoggedIn::swapWidgetsReturn() {
    QWidget* pOldWidget = this->pCentralWidget;
    this->pCentralWidget = new MainWindow(nullptr);

    this->pLayout->removeWidget(pOldWidget);
    pLayout->addWidget(pCentralWidget);

    pOldWidget->hide();
    delete pOldWidget;
}

void NotLoggedIn::onReturn() {
    emit this->returned();

}
