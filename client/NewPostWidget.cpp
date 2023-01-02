//
// Created by mrnk on 1/2/23.
//

#include <QVBoxLayout>
#include "NewPostWidget.h"
#include "ServerConnection.h"
#include "../common/common.h"
NewPostWidget::NewPostWidget(QWidget *pParent) : QWidget(pParent) {
    this->initWidget();
}

void NewPostWidget::initWidget() {
    this->createComponents();
    this->settleLayouts();
}

void NewPostWidget::createComponents() {
    this->pMainLayout = new QVBoxLayout (this);
    this->pTextBoxLayout = new QVBoxLayout ();
    this->pButtonsLayout = new QHBoxLayout();

    this->pPostButton = new QPushButton (NewPostWidget :: pPostButtonText, this);
    this->pTextEdit = new QTextEdit(this);

    if(this->isPrivateVariable)
    {
        this->pPostToWhichGroup = new QComboBox(this);
        this->pPostToWhichGroup->addItem(QStringLiteral("Public"));
        this->pPostToWhichGroup->addItem(QStringLiteral("Friends"));
        this->pPostToWhichGroup->addItem(QStringLiteral("Close Friends"));
        this->pPostToWhichGroup->addItem(QStringLiteral("Acquaintances"));
    }
}

void NewPostWidget::settleLayouts() {
    this->setLayout(this->pMainLayout);
    this->pMainLayout->addItem(pTextBoxLayout);
    this->pMainLayout->addItem(pButtonsLayout);

    this->pTextBoxLayout->addWidget(this->pTextEdit);

    if(this->isPrivateVariable)
    {
        this->pButtonsLayout->addWidget(this->pPostToWhichGroup);
    }
    this->pButtonsLayout ->addWidget(this->pPostButton);

}
void NewPostWidget::changePostVisibility(const std::string &) {

}

bool NewPostWidget::isPrivate() {
    common::writeRequest(ServerConnection::getInstance().getSocket(),common::ClientRequests::REQUEST_GET_PRIVACY_TYPE);

    common::ServerResponse response = common::readResponse(ServerConnection::getInstance().getSocket());
    switch (response) {
        case common::ServerResponse::PRIVACY_TYPE_PRIVATE:
           this->isPrivateVariable = true;
           break;
        case common::ServerResponse::PRIVACY_TYPE_PUBLIC:
            this->isPrivateVariable = false;
            break;
    }
}
