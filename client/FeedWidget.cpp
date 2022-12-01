//
// Created by loghin on 01/12/22.
//

#include "FeedWidget.h"
#include <qwidget.h>
#include <QStyleOption>


FeedWidget:: FeedWidget(MainWindow * pParentWindow)  :
        QWidget ( pParentWindow ),
        pParent ( pParentWindow ) {
    this->initWidget();
}

void FeedWidget ::initWidget() {
    this->createComponents();
    this->settleComponents();
}

void FeedWidget::createComponents() {
    this->pLayout = new QHBoxLayout(this);

}

void FeedWidget ::settleComponents() {

}

