//
// Created by mrnk on 12/25/22.
//

#include <QHBoxLayout>
#include "SettingsWidget.h"
#include "../../common/common.h"
#include "../ServerConnection.h"
using namespace common;

SettingsWidget::SettingsWidget(QWidget *pParent) :
        QWidget(pParent){
    this->initWidget();

}

void SettingsWidget::initWidget() {
    this->createComponents();
    this->settleLayouts();
    connect(this->pApplyChangesButton, &QPushButton::clicked, this, &SettingsWidget::applyChanges);

}

void SettingsWidget::createComponents() {
    this->pMainLayout = new QHBoxLayout(this);

    this->pChangePrivacyBox = new QComboBox(this);
    this->pChangePrivacyBox->addItem("Public");
    this->pChangePrivacyBox->addItem("Private");
    this->pCurrentPrivacySetting = new QLabel ("");
    this->getPrivacy();
    this->pApplyChangesButton = new QPushButton(SettingsWidget::pApplyChangesButtonText, this);

    connect(this->pChangePrivacyBox,SIGNAL(currentIndexChanged(int)), this, SLOT(changePrivacy(int)));
}

void SettingsWidget::settleLayouts() {
    this->setLayout(this->pMainLayout);

    this->pMainLayout->addWidget(this->pCurrentPrivacySetting);
    this->pMainLayout->addWidget(this->pChangePrivacyBox);
    this->pMainLayout->addWidget(this->pApplyChangesButton);
}

void SettingsWidget::getPrivacy() {
    common::writeRequest(ServerConnection::getInstance().getSocket(),common::ClientRequests::REQUEST_GET_PRIVACY_TYPE);

    ServerResponse response = readResponse(ServerConnection::getInstance().getSocket());
    switch (response) {
        case ServerResponse::PRIVACY_TYPE_PRIVATE:
            this->pCurrentPrivacySetting->setText(SettingsWidget::pPrivateAccountText);
            this->pChangePrivacyBox->setCurrentIndex(1);
            break;
        case ServerResponse::PRIVACY_TYPE_PUBLIC:
            this->pCurrentPrivacySetting->setText(SettingsWidget::pPublicAccountText);
            this->pChangePrivacyBox->setCurrentIndex(0);
            break;
    }
}

void SettingsWidget::refresh() {
    //schimb textul de la privacy daca e nevoie
    this->getPrivacy();
}

void SettingsWidget::changePrivacy(int index) {
    switch(index)
    {
        case 0://public
            this->sendChangePrivacyRequest(common::privacySetting::PUBLIC);
            break;
        case 1://private
            this->sendChangePrivacyRequest(common::privacySetting::PRIVATE);
            break;


    }
}

void SettingsWidget::applyChanges() {
    this->refresh();
}

void SettingsWidget::sendChangePrivacyRequest(common::privacySetting privacyType) {
    switch (privacyType) {
        case common::privacySetting::PUBLIC:
            common::writeRequest(ServerConnection::getInstance().getSocket(), common::ClientRequests::REQUEST_CHANGE_PRIVACY_TYPE_PUBLIC);
            break;
        case common::privacySetting::PRIVATE:
            common::writeRequest(ServerConnection::getInstance().getSocket(), common::ClientRequests::REQUEST_CHANGE_PRIVACY_TYPE_PRIVATE);
            break;
    }
}
