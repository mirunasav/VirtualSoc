//
// Created by mrnk on 12/19/22.
//

#include <QVBoxLayout>
#include <QMessageBox>
#include "AddFriendsWidget.h"

AddFriendsWidget::AddFriendsWidget(QWidget *pParentWindow) :
                QWidget (pParentWindow) {
    this->initWidget();
}

void AddFriendsWidget::initWidget() {
 /*   QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->show();
*/
    this->createComponents();
    this->settleLayouts();

    connect(this->pSendRequestButton, &QPushButton :: clicked,this, &AddFriendsWidget::onSendRequest);

}

void AddFriendsWidget::createComponents() {
    this->pCenterLayout = new QVBoxLayout ();
    this->pMainLayout= new QVBoxLayout ();
    this->pLineEditLayout = new QHBoxLayout ();
    this->pLabelLayout = new QVBoxLayout ();
    this->pTextBoxLayout = new QVBoxLayout ();
    this->pButtonLayout = new QVBoxLayout ();

    this->pSearchUserLabel = new QLabel (AddFriendsWidget :: pSearchUserText, this);
    this->pSendRequestTextBox = new QLineEdit(this);

    this->pSendRequestButton = new QPushButton (AddFriendsWidget:: pSendRequestButtonText, this);
    this->pSendRequestButton->setAutoFillBackground(true);
    QPalette buttonPalette = this->pSendRequestButton->palette();
    buttonPalette.setColor(QPalette::Base, QColor(Qt::blue));
    this->pSendRequestButton ->setPalette(buttonPalette);
    this->pSendRequestButton->show();

}

void AddFriendsWidget::settleLayouts() {
  /*  this->pMainLayout ->addItem(this->pCenterLayout);
    this->pCenterLayout ->addItem(this->pLineEditLayout);
    this->pCenterLayout ->addItem(this->pButtonLayout);
    this->pCenterLayout ->addWidget(this->pSendRequestButton);

    this->pLineEditLayout->addItem (this->pLabelLayout);
    this->pLineEditLayout->addItem (this->pTextBoxLayout);

    this -> pTextBoxLayout ->addWidget(this->pSendRequestTextBox);
    this->pLabelLayout ->addWidget(this->pSearchUserLabel);

    this->pCenterLayout->setAlignment(Qt::AlignCenter);

    this->pCenterLayout->setContentsMargins(sizeHint().width() /3, 0, sizeHint().height() / 3, 0);

    this->setMinimumWidth( sizeHint().width()/ 3 * 2 + 200 );
    this->setMinimumHeight( sizeHint().height()/ 2 );

    this->pSendRequestButton->setMaximumWidth( 75 );
    this->pButtonLayout->setAlignment( Qt::AlignCenter);*/
  this->pMainLayout ->addWidget(this->pSendRequestButton);
  this->pMainLayout ->setAlignment(Qt::AlignRight);

}

void AddFriendsWidget::onSendRequest(){
    if(this->userExists()) //pop up box cu a fost trimisa cererea
    {
        this->notificationPopUp(AddFriendsWidget::pRequestSentText);
    }
    else
        //pop up box cu eroare, username invalid ( exista sau suntem chiar noi )
    {
        this->notificationPopUp(AddFriendsWidget :: pInvalidUserText);
    }
        // emit this->requestSent();
}
void AddFriendsWidget::notificationPopUp(const char *message) {
    //apare un text box pop up; parintele este this
    //titlul este ..., mesajul este message, un buton de ok
    QMessageBox::information(this, " ", message,QMessageBox::Ok);

}

bool AddFriendsWidget::userExists() {
    //verific cu serverul daca exista
}

