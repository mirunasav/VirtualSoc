//
// Created by mrnk on 1/10/23.
//

#include <QHBoxLayout>
#include "BlockedItem.h"


BlockedItem::BlockedItem(QWidget *pParent, const std::string &username) : QWidget(pParent){
    this->initWidget(username);
}

void BlockedItem::initWidget(const std::string &username) {
    this->createComponents(username);
    this->settleLayouts();

    connect(this->pUnblockButton,  &QPushButton ::clicked, this, &BlockedItem ::onUnblockClick);
    connect(this, SIGNAL(unblock(const std::string &)), this->parent(), SLOT(unblock(const std::string &)));

}

void BlockedItem::createComponents(const std::string &username) {
    this->pMainLayout = new QHBoxLayout(this);
    this->pLabelsLayout = new QHBoxLayout(nullptr);
    this->pButtonsLayout= new QHBoxLayout(nullptr);

    this->pUnblockButton = new QPushButton (BlockedItem ::pUnblockButtonText, this);

    this->pUsername = new QLabel (username.c_str(), this);
}

void BlockedItem::settleLayouts() {
    this->setLayout(this->pMainLayout);
    this->pMainLayout->addItem(this->pLabelsLayout);
    this->pMainLayout->addItem(this->pButtonsLayout);

    this->pLabelsLayout ->addWidget(this->pUsername);
    this->pButtonsLayout->addWidget(this->pUnblockButton);

    this->pMainLayout->setAlignment(Qt::AlignLeft);
    this->pMainLayout->setAlignment(this->pButtonsLayout, Qt::AlignLeft);


    this->pUsername->setStyleSheet("QLabel {"
                                   "border-style: hidden;"
                                   "border-radius: 8px;"
                                   "border-width: 1px;"
                                   "padding: 3px;"
                                   "}");
}
void BlockedItem::onUnblockClick() {
    emit unblock(this->pUsername->text().toStdString());
}