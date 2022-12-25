//
// Created by loghin on 01/12/22.
//

#include "AppHomeWidget.h"
#include <qwidget.h>
#include <QStyleOption>
#include "FeedWidget.h"
#include "ActionsWidget.h"
#include "Friends/FriendsMenuWidget.h"
#include "SettingsWidget.h"

AppHomeWidget:: AppHomeWidget(QWidget * pParentWindow)  :
        QWidget ( pParentWindow )
         {
    this->initWidget();
}

void AppHomeWidget ::initWidget() {

    this->createComponents();
    this->settleLayouts();
    this->styleComponents();

}

void AppHomeWidget::createComponents() {
  this->pCentralWidget = new QWidget(this);

 // this->pHomeWidgetTitle = new QLabel(this->pHomeWidgetTitleLabel, this);

  this->pLayout = new QHBoxLayout();
  this->pMainLayout = new QHBoxLayout();

  this->pFeedWidget = new FeedWidget(this);
  this->pActionsWidget = new ActionsWidget(this);

  this->pSplitter = new QSplitter(Qt::Horizontal);

}

void AppHomeWidget ::settleLayouts() {
    this->setLayout(this->pMainLayout);

    this->pMainLayout->addWidget(this->pCentralWidget);
    this->pCentralWidget->setLayout(this->pLayout);
   // this->pLayout->addWidget(this->pActionsWidget);
   // this->pLayout->addWidget(this->pFeedWidget);
   this->pLayout ->addWidget(this->pSplitter);
   this->pSplitter->addWidget(this->pActionsWidget);
   this->pSplitter->addWidget(this->pFeedWidget);
}

void AppHomeWidget :: styleComponents()
{
    this->pSplitter->setSizes(QList <int>{sizeHint().width()*1/3, sizeHint().width()*2/3*7});
}

void AppHomeWidget::swapWidgetsLogOut() {
    QWidget* pOldWidget = this->pCentralWidget; //retin widgetul activ
    this->pCentralWidget = new MainWindow(nullptr);//setez un home widget ca activ

    //in loc de setCentralWidget
//    this->pLayout = new QVBoxLayout();
//    this->setLayout(pLayout);
    this->pMainLayout->removeWidget(pOldWidget);
    pMainLayout->addWidget(pCentralWidget);//activez widgetul

    pOldWidget->hide();
    delete pOldWidget;
}

void AppHomeWidget::swapWidgetsFriendsMenu() {

    QWidget *pOldWidget = this->pFeedWidget;

    this->pFeedWidget = new FriendsMenuWidget(this);

    this->pSplitter->replaceWidget(1, this->pFeedWidget);

    pOldWidget->hide();
    delete pOldWidget;

}

void AppHomeWidget::swapWidgetsSettings() {
    QWidget *pOldWidget = this->pFeedWidget;

    this->pFeedWidget = new SettingsWidget(this);

    this->pSplitter->replaceWidget(1, this->pFeedWidget);

    pOldWidget->hide();
    delete pOldWidget;
}



