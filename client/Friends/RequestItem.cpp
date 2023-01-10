//
// Created by mrnk on 1/7/23.
//

#include <QHBoxLayout>
#include "RequestItem.h"


RequestItem::RequestItem(QWidget *pParent, const std::string &username) : QWidget(pParent){
    this->initWidget(username);
}
void RequestItem::initWidget(const std::string &username) {
    this->createComponents(username);
    this->settleLayouts();

    connect(this->pAcceptButton,  &QPushButton ::clicked, this, &RequestItem ::onAcceptClick);
    connect(this->pDenyButton,  &QPushButton ::clicked, this, &RequestItem ::onDenyClick);
    connect(this->pBlockButton,  &QPushButton ::clicked, this, &RequestItem ::onBlockClick);

    connect(this, SIGNAL(accept(const std::string &)), this->parent(), SLOT(acceptRequest(const std::string &)));
    connect(this, SIGNAL(deny(const std::string &)), this->parent(), SLOT(denyRequest(const std::string &)));
    connect(this, SIGNAL(block(const std::string &)), this->parent(), SLOT(blockUser(const std::string &)));
}

void RequestItem::createComponents(const std::string &username) {
    this->pMainLayout = new QHBoxLayout(this);
    this->pLabelsLayout = new QHBoxLayout(nullptr);
    this->pButtonsLayout= new QHBoxLayout(nullptr);

    this->pAcceptButton = new QPushButton (RequestItem ::pAcceptButtonText, this);
    this->pDenyButton = new QPushButton (RequestItem ::pDenyButtonText, this);
    this->pBlockButton = new QPushButton (RequestItem ::pBlockButtonText, this);

    this->pUsername = new QLabel (username.c_str(), this);
}

void RequestItem::settleLayouts() {
    this->setLayout(this->pMainLayout);
    this->pMainLayout->addItem(this->pLabelsLayout);
    this->pMainLayout->addItem(this->pButtonsLayout);

    this->pLabelsLayout ->addWidget(this->pUsername);
    this->pButtonsLayout->addWidget(this->pAcceptButton);
    this->pButtonsLayout->addWidget(this->pDenyButton);
    this->pButtonsLayout->addWidget(this->pBlockButton);

    this->pMainLayout->setAlignment(Qt::AlignLeft);
    this->pMainLayout->setAlignment(this->pButtonsLayout, Qt::AlignLeft);


    this->pUsername->setStyleSheet("QLabel {"
                                         "border-style: hidden;"
                                         "border-radius: 8px;"
                                         "border-width: 1px;"
                                         "padding: 3px;"
                                         "}");
}
void RequestItem::onAcceptClick() {
    emit accept(this->pUsername->text().toStdString());
}

void RequestItem::onDenyClick() {
    emit deny(this->pUsername->text().toStdString());
}

void RequestItem::onBlockClick() {
    emit block(this->pUsername->text().toStdString());
}


