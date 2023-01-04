//
// Created by mrnk on 12/28/22.
//

#include <QVBoxLayout>
#include <QTimer>
#include <QLineEdit>
#include "../ServerConnection.h"
#include "ChatWidget.h"
#include "../../common/common.h"
#include "../MainWindow.h"
#include <QKeyEvent>

ChatWidget::ChatWidget(QWidget *pParent, std::string &usernamesInChat) :
        QWidget(pParent){
    this->initWidget(usernamesInChat);
}

void ChatWidget::initWidget(std::string & usernamesInChat) {
    this->createComponents(usernamesInChat);
    this->settleLayouts();
    this->acquireChatFile();



}

void ChatWidget::createComponents(std::string & usernamesInChat) {
    this->pMainLayout = new QVBoxLayout (this);
    this->pUsersInChatLayout = new QVBoxLayout ();
    this->pMessagesLayout= new QVBoxLayout ();
    this->pSendMessageLayout= new QHBoxLayout ();
    this->pButtonLayout= new QHBoxLayout ();

    this->pSendMessageLineEdit = new QLineEdit(this);
    this->pSendMessageButton = new QPushButton(ChatWidget::pSendMessageButtonText, this);

    this->usersInChat = usernamesInChat;
    this->usersInChatParsedLabel = this->parseString(this->usersInChat);
    this->pUsersInChatLabel = new QLabel (this->usersInChatParsedLabel.c_str(), this);
    this->pUsersInChatLabel->setFont(this->usersInChatLabelFont);

    this->pMessagesList = new QListWidget(this);
    this->pRefreshChatTimer = new QTimer (this);

    connect(this->pSendMessageButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(this->pRefreshChatTimer, SIGNAL(timeout()), this, SLOT(acquireChatFile()));
}


void ChatWidget::settleLayouts() {
    this->setLayout(this->pMainLayout);

    this->pMainLayout->addItem(this->pUsersInChatLayout);
    this->pMainLayout->addItem(this->pMessagesLayout);
    this->pMainLayout->addItem(this->pSendMessageLayout);

    this->pUsersInChatLayout->addWidget(this->pUsersInChatLabel);

    this->pMessagesLayout->addWidget(this->pMessagesList);
    this->pMessagesLayout->setAlignment(Qt::AlignLeft);

    this->pSendMessageLayout->addWidget(this->pSendMessageLineEdit);
    this->pSendMessageLayout->addWidget(this->pSendMessageButton);

    this->pMessagesList->setContentsMargins(MainWindow::WIDTH / 20, 0, MainWindow::WIDTH / 20, 0);

}


void ChatWidget::acquireChatFile() {
    this->pRefreshChatTimer->stop();

  try {

      common::writeRequest(ServerConnection::getInstance().getSocket(),
                           common::ClientRequests::REQUEST_GET_CHAT_FILE_READ);
      common::writeString(ServerConnection::getInstance().getSocket(), this->usersInChat);

      int linesUserSees = this->pMessagesList->count();
      common::writeRequestNumber(ServerConnection::getInstance().getSocket(), linesUserSees);

      int linesServerSends = 0;
      std::string message;
      common::readBufferInt(ServerConnection::getInstance().getSocket(), linesServerSends);

      for (int i = 1; i <= linesServerSends; i++) {
          message = common::readString(ServerConnection::getInstance().getSocket());
          this->addMessage(message);
      }
      this->pMessagesList->scrollToBottom();

  }
  catch( std::exception const & ex ) //daca e vreo exceptie, ne reconectam
  {
      ServerConnection::getInstance().connect(common::SERVER_IP, common::SERVER_PORT);
  }
    this->restartTimer();
}

void ChatWidget::addMessage(std::string message) {
    auto *pItem = new QListWidgetItem(this->pMessagesList);//intermediar

    auto *pWidget = new QLabel(message.c_str(), this);

    pItem->setSizeHint(pWidget->minimumSizeHint());

    pItem->setFlags(pItem->flags() & ~(Qt::ItemIsEnabled));

    this->pMessagesList->addItem(pItem);  /// adaugam intermediarul in lista
    this->pMessagesList->setItemWidget(pItem, pWidget);///asociem intermediarul cu widgetul
}

void ChatWidget::restartTimer() {
    this->pRefreshChatTimer->setInterval(1500);
    this->pRefreshChatTimer->start();
}

std::string ChatWidget::parseString(std::string stringToParse ) {
//AICI O SA despart users in chat ca sa nu apara cu |
   const char * delimitator = "|";
   std::vector <std::string> vectorOfUsernames = common::tokenizeString(this->usersInChat, delimitator);
   return common::vectorToString(vectorOfUsernames, ", ");
}

void ChatWidget::sendMessage() {
    std::string messageToSend = this->pSendMessageLineEdit->text().toStdString();
    this->pSendMessageLineEdit->clear();
    try
    {
        common::writeRequest(ServerConnection::getInstance().getSocket(), common::ClientRequests::REQUEST_GET_CHAT_FILE_WRITE);
        common::writeString(ServerConnection::getInstance().getSocket(), this->usersInChat);
        common::writeString(ServerConnection::getInstance().getSocket(),messageToSend);
        this->acquireChatFile();

    }
    catch( std::exception const & ex ) //daca e vreo exceptie, ne reconectam
    {
        ServerConnection::getInstance().connect(common::SERVER_IP, common::SERVER_PORT);
    }

}

void ChatWidget::keyPressEvent(QKeyEvent *event) {

    if( event ->key() == Qt::Key_Return || event ->key() == Qt::Key_Enter)
    {
        this->sendMessage();
    }
}
