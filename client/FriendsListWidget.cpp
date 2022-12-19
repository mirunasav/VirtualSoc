//
// Created by mrnk on 12/14/22.
//

#include <QVBoxLayout>
#include "FriendsListWidget.h"

FriendsListWidget::FriendsListWidget(QWidget *pParentWindow) :
            QWidget(pParentWindow){
        this->initWidget();

}

void FriendsListWidget::initWidget() {
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->show();
    createComponents();
    settleLayouts();
}

void FriendsListWidget::createComponents() {
    this->pLayout = new QVBoxLayout(this);
}

void FriendsListWidget::settleLayouts() {
    this->setLayout(this->pLayout);
}
