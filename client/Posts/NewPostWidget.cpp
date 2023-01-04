//
// Created by mrnk on 1/2/23.
//

#include <QVBoxLayout>
#include <QMessageBox>
#include <QDateTime>
#include "NewPostWidget.h"
#include "../ServerConnection.h"
#include "../../common/common.h"
#include "../LogInInterface/MainWindow.h"
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

    if(this->isPrivate())
    {
        this->pVisibleToWhomComboBox = new QComboBox(this);
        this->pVisibleToWhomComboBox->addItem(QStringLiteral("Public"));
        this->pVisibleToWhomComboBox->addItem(QStringLiteral("Friends"));
        this->pVisibleToWhomComboBox->addItem(QStringLiteral("Close Friends"));
        this->pVisibleToWhomComboBox->addItem(QStringLiteral("Acquaintances"));
    }

    connect(this->pPostButton, &QPushButton ::clicked, this, &NewPostWidget::onPostClick);
}

void NewPostWidget::settleLayouts() {
    this->setLayout(this->pMainLayout);
    this->pMainLayout->addItem(pTextBoxLayout);
    this->pMainLayout->addItem(pButtonsLayout);

    this->pTextBoxLayout->addWidget(this->pTextEdit);

    if(this->isPrivateVariable)
    {
        this->pButtonsLayout->addWidget(this->pVisibleToWhomComboBox);
    }
    this->pButtonsLayout ->addWidget(this->pPostButton);

    this->pMainLayout->setContentsMargins(MainWindow::WIDTH/10, MainWindow::HEIGHT/10,MainWindow::WIDTH/10, MainWindow::HEIGHT/10);

}

bool NewPostWidget::isPrivate() {
    common::writeRequest(ServerConnection::getInstance().getSocket(),common::ClientRequests::REQUEST_GET_PRIVACY_TYPE);

    common::ServerResponse response = common::readResponse(ServerConnection::getInstance().getSocket());
    switch (response) {
        case common::ServerResponse::PRIVACY_TYPE_PRIVATE:
           this->isPrivateVariable = true;
           return true;
        case common::ServerResponse::PRIVACY_TYPE_PUBLIC:
            this->isPrivateVariable = false;
            return false;
    }
}

void NewPostWidget::onPostClick() {
    //pun in variabile textul postarii si ce e ales in combobox
    this->textOfPost = this->pTextEdit->toPlainText().toStdString();
    if(this->isPrivate())
    {
        switch(this->pVisibleToWhomComboBox->currentIndex())
        {
            case 0://public
                this->visibleToWhom = "0";
                break;
            case 1:
                this->visibleToWhom = "1";
                break;
            case 2:
                this->visibleToWhom = "2";
                break;
            case 3:
                this->visibleToWhom = "3";
                break;

        }
    }
    else
        this->visibleToWhom = "0";

    common::writeRequest(ServerConnection::getInstance().getSocket(), common::ClientRequests::REQUEST_NEW_POST);
    common::writeString(ServerConnection::getInstance().getSocket(),this->textOfPost);
    common::writeString(ServerConnection::getInstance().getSocket(),this->visibleToWhom);

    QDateTime date = QDateTime ::currentDateTime();
    QString formattedTime = date.toString("hh:mm,    dd.MM.yyyy ");

    common::writeString(ServerConnection::getInstance().getSocket(), formattedTime.toStdString());

    this->notificationPopUp(NewPostWidget::pAfterPostingMessage);

    if(this->isPrivate())
        this->pVisibleToWhomComboBox->setCurrentIndex(0);
    this->pTextEdit->clear();

}

void NewPostWidget::notificationPopUp(const char *message) {
    QMessageBox::information(this, " ", message,QMessageBox::Ok);
}
