//
// Created by mrnk on 12/29/22.
//

#include <QVBoxLayout>
#include <QLabel>
#include "AllMessagesWidget.h"
#include "../../common/common.h"
#include "../ServerConnection.h"

AllMessagesWidget::AllMessagesWidget(QWidget *pParent):
        QWidget(pParent){
    this->initWidget();
}

void AllMessagesWidget::initWidget() {
    this->createComponents();
    this->settleLayouts();
    connect(this->pAllChatsList, SIGNAL(itemDoubleClicked(QListWidgetItem *)),this, SLOT(onDoubleClick(QListWidgetItem *)));
    connect(this, SIGNAL( sendMessage(std::string &)), this->parent(),SLOT(swapWidgetsSendMessage(std::string &)));
}

void AllMessagesWidget::createComponents() {
    this->createListWidget();
    this->pMainLayout = new QVBoxLayout (this);

}

void AllMessagesWidget::createListWidget() {
    this->pAllChatsList = new QListWidget;
    QStringList listOfChats;

    this->acquireAllChatsList(listOfChats);

    this->pAllChatsList->addItems(listOfChats);

    this->pAllChatsList->setStyleSheet(
            "QListWidget {"
            "background-color:#263440;"
            "font : 25px;"
            "}"
    );
}


void AllMessagesWidget::settleLayouts() {
    this->setLayout(this->pMainLayout);

    this->pMainLayout->addWidget(this->pAllChatsList);

}

void AllMessagesWidget::acquireAllChatsList(QStringList& chatsList) {
    try {
        common::writeRequest(ServerConnection::getInstance().getSocket(), common::ClientRequests::REQUEST_GET_ALL_CHATS);
        int numberOfChats = 0;
        std::string usersInChat;

        common::readBufferInt(ServerConnection::getInstance().getSocket(),numberOfChats);

        for(int i = 0; i < numberOfChats; i++)
        {
           usersInChat = common::readString(ServerConnection::getInstance().getSocket());
           chatsList << usersInChat.c_str();
        }

    }
    catch ( std::exception const & ex ) //daca e vreo exceptie, ne reconectam
    {
        ServerConnection::getInstance().connect(common::SERVER_IP, common::SERVER_PORT);
    }

}

void AllMessagesWidget::onDoubleClick(QListWidgetItem *item) {
    std::string chatSelected;
    //transmitem toti userii, dar facand replace la virgula cu '|' si adaugand la final '|'
    chatSelected = item->text().toStdString();
    std::replace(chatSelected.begin(), chatSelected.end(), ',', '|');
    chatSelected.append("|");
    emit sendMessage(chatSelected);

}

