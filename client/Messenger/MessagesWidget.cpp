//
// Created by mrnk on 12/26/22.
//

#include <QVBoxLayout>
#include "MessagesWidget.h"
#include "../MainWindow.h"
#include "NewMessageWidget.h"
#include "ChatWidget.h"
#include "AllMessagesWidget.h"

MessagesWidget::MessagesWidget(QWidget *pParent) : QWidget(pParent){
    this->initWidget();
}

void MessagesWidget::initWidget() {
    this->createComponents();
    this->settleLayouts();
    this->styleComponents();

    connect(this->pAllMessagesButton, &QPushButton :: clicked,this, &MessagesWidget::swapWidgetsAllMessages);
    connect(this->pNewMessageButton, &QPushButton :: clicked,this, &MessagesWidget::swapWidgetsNewMessage);
}

void MessagesWidget::createComponents() {
    this->pHorizontalSplitter= new QSplitter (Qt::Horizontal);
    this->pVerticalSplitter = new QSplitter (Qt::Vertical);

    this->pChangeableWidget = new AllMessagesWidget(this);
    this->pButtonsWidget = new QWidget(this);

    this->pMainLayout = new QVBoxLayout(this);
    this->pButtonsLayout = new QVBoxLayout();

    this->pMessagesLabel = new QLabel(MessagesWidget::pAllMessagesLabelText);
    this->pMessagesLabel->setAlignment(Qt::AlignCenter);
    this->pMessagesLabel->setFont(this->MessagesLabelFont);

    this->pAllMessagesButton = new QPushButton(MessagesWidget::pAllMessagesButtonText);
    this->pNewMessageButton = new QPushButton(MessagesWidget::pNewMessageButtonText);

}

void MessagesWidget::settleLayouts() {
    this->setLayout(this->pMainLayout);
    this->pButtonsWidget->setLayout(this->pButtonsLayout);

    this->pMainLayout->addWidget(this->pHorizontalSplitter);
    this->pMainLayout->addWidget(this->pVerticalSplitter);

    this->pHorizontalSplitter ->addWidget(this->pButtonsWidget);
    this->pHorizontalSplitter->addWidget(this->pChangeableWidget);

    this->pVerticalSplitter ->addWidget(this->pMessagesLabel);
    this->pVerticalSplitter ->addWidget(this->pHorizontalSplitter);

    this->pButtonsLayout->addWidget(this->pAllMessagesButton);
    this->pButtonsLayout->addWidget(this->pNewMessageButton);

   this->pButtonsLayout->setContentsMargins( 0, MainWindow::HEIGHT/3,0,MainWindow::HEIGHT/2.5);
   this->pButtonsLayout->setAlignment(Qt::AlignCenter);

}

void MessagesWidget::styleComponents() {
    this->pHorizontalSplitter->setSizes(QList <int>{sizeHint().width()*1/3, sizeHint().width()*7/3*5});
    this->pVerticalSplitter->setSizes(QList <int>{sizeHint().height()*1/3, sizeHint().height()*7/3*5});
}

void MessagesWidget::swapWidgetsAllMessages() {
    QWidget *pOldWidget = this->pChangeableWidget;

    this->pChangeableWidget = new AllMessagesWidget(this);

    this->pHorizontalSplitter->replaceWidget(1, this->pChangeableWidget);

    this->pMessagesLabel->setText(MessagesWidget::pAllMessagesLabelText);

    pOldWidget->hide();
    delete pOldWidget;
}

void MessagesWidget::swapWidgetsNewMessage() {
    QWidget *pOldWidget = this->pChangeableWidget;

    this->pChangeableWidget = new NewMessageWidget(this);

    this->pHorizontalSplitter->replaceWidget(1, this->pChangeableWidget);

    this->pMessagesLabel->setText(MessagesWidget::pNewMessageLabelText);

    pOldWidget->hide();
    delete pOldWidget;
}

void MessagesWidget::swapWidgetsSendMessage(std::string & selectedUsernames) {
    QWidget *pOldWidget = this->pChangeableWidget;

    this->pChangeableWidget = new ChatWidget(this,selectedUsernames);

    this->pHorizontalSplitter->replaceWidget(1, this->pChangeableWidget);

    this->pMessagesLabel->setText(MessagesWidget::pChatsLabelText);

    pOldWidget->hide();
    delete pOldWidget;
}
