//
// Created by mrnk on 12/23/22.
//

#include <QHBoxLayout>
#include "FriendItem.h"
#include <string>
#include "../../common/common.h"


FriendItem::FriendItem(QWidget *pParent,const std::string & username ,const std::string & friendshipType):
        QWidget(pParent)
{
    this->initWidget(username, friendshipType);
}

void FriendItem::initWidget(const std::string &username ,const std::string  & friendshipType) {
    this->createComponents(username, friendshipType);
    this->settleLayouts();

    connect(this->pRemoveFriendButton, &QPushButton ::clicked, this, &FriendItem ::onRemoveClick);
    connect (this, SIGNAL(remove(const std::string &)), this->parent(), SLOT(removeFriend(const std::string &  )));
    connect (this, SIGNAL(changeType(const std::string &, const std::string &)), this->parent(), SLOT(changeFriendshipType(const std::string &, const std::string &) ));

    connect(this->pApplyChangeButton, &QPushButton::clicked, this, &FriendItem::onApplyChangeClick);
    connect(this, SIGNAL(applyChange()), this->parent(), SLOT(refreshFriendList()));
}

void FriendItem::createComponents(const std::string &username ,const std::string &friendshipType) {
    this->pMainLayout = new QHBoxLayout(this);
    this->pLabelsLayout = new QHBoxLayout(nullptr);
    this->pButtonsLayout= new QHBoxLayout(nullptr);

    this->pRemoveFriendButton = new QPushButton (FriendItem::pRemoveFriendButtonText, this);
    this->pApplyChangeButton = new QPushButton(FriendItem::pApplyChangeButtonText, this);

    this->pChangeFriendType = new QComboBox(this);
    this->pChangeFriendType->addItem(QStringLiteral("Normal Friend"));
    this->pChangeFriendType->addItem(QStringLiteral("Close Friend"));
    this->pChangeFriendType->addItem(QStringLiteral("Acquaintance"));
    auto type = static_cast <common::typesOfFriend> (stoi(friendshipType));
    switch(type)
    {
        case common::typesOfFriend::NORMAL_FRIEND:
            this->pChangeFriendType->setCurrentIndex(0);
            break;
        case common::typesOfFriend::CLOSE_FRIEND:
            this->pChangeFriendType->setCurrentIndex(1);
            break;
        case common::typesOfFriend::Acquaintance:
            this->pChangeFriendType->setCurrentIndex(2);
            break;
    }

    connect(this->pChangeFriendType, SIGNAL(currentIndexChanged(int)), this, SLOT(onChangeTypeClick(int)));

    this->pFriendUsername = new QLabel (username.c_str(), this);

    switch(type)
    {
        case common::typesOfFriend::NORMAL_FRIEND:
            this->pFriendshipType = new QLabel ("Friend",this);
            break;
        case common::typesOfFriend::CLOSE_FRIEND:
            this->pFriendshipType = new QLabel ("Close Friend",this);
            break;
        case common::typesOfFriend::Acquaintance:
            this->pFriendshipType = new QLabel ("Acquaintance",this);
            break;

    }

}

void FriendItem::settleLayouts() {
    this->setLayout(this->pMainLayout);
    this->pMainLayout->addItem(this->pLabelsLayout);
    this->pMainLayout->addItem(this->pButtonsLayout);

    this->pLabelsLayout->addWidget(this->pFriendUsername);
    this->pLabelsLayout->addWidget(this->pFriendshipType);
    this->pButtonsLayout->addWidget(this->pChangeFriendType);
    this->pButtonsLayout->addWidget(this->pApplyChangeButton);
    this->pButtonsLayout->addWidget(this->pRemoveFriendButton);

    this->pMainLayout->setAlignment(Qt::AlignLeft);
    this->pMainLayout->setAlignment(this->pButtonsLayout, Qt::AlignLeft);

    this->pFriendUsername->setStyleSheet("QLabel {"
                                         "border-style: hidden;"
                                         "border-radius: 8px;"
                                         "border-width: 1px;"
                                         "padding: 3px;"
                                         "}");
    this->pFriendshipType->setStyleSheet("QLabel {"
                                         "border-style: hidden;"
                                         "border-radius: 8px;"
                                         "border-width: 1px;"
                                         "padding: 3px;"
                                         "}");


}

void FriendItem::onRemoveClick() {
    emit remove(this->pFriendUsername->text().toStdString());
}

void FriendItem::
onChangeTypeClick(int index) {
    switch(index)
    {
        case 0://Normal friend
            emit changeType(this->pFriendUsername->text().toStdString(),std::to_string(common::typesOfFriend::NORMAL_FRIEND));
            break;
        case 1://Close Friend
            emit changeType(this->pFriendUsername->text().toStdString(),std::to_string(common::typesOfFriend::CLOSE_FRIEND));
            break;
        case 2://Acquaintance
            emit changeType(this->pFriendUsername->text().toStdString(),std::to_string(common::typesOfFriend::Acquaintance));
            break;

    }
}

void FriendItem::onApplyChangeClick() {
    emit applyChange();
}


