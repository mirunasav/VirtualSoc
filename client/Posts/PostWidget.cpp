//
// Created by mrnk on 1/3/23.
//

#include <QVBoxLayout>
#include "PostWidget.h"

PostWidget::PostWidget(QWidget *pParentWidget,int ID, const std::string &isOwnerOfPost , const std::string &userWhoPosts, const std::string &textOfPost, const std::string &visibleToWhom, const std::string & dateOfPost) :
        QWidget(pParentWidget){
    if(isOwnerOfPost == "true")
        this->isOwnerOfPost = true;
    else
        this->isOwnerOfPost = false;
    this->postID = ID;

    this->initWidget(userWhoPosts, textOfPost, visibleToWhom, dateOfPost);

}

void PostWidget::initWidget(const std::string &userWhoPosts, const std::string &textOfPost, const std::string &visibleToWhom, const std::string &dateOfPost) {
    this->createComponents(userWhoPosts, textOfPost, visibleToWhom, dateOfPost);
    this->settleLayouts();
}

void PostWidget::createComponents(const std::string &userWhoPosts, const std::string &textOfPost, const std::string &visibleToWhom, const std::string &dateOfPost) {
    this->pMainLayout = new QVBoxLayout (this);
    this->pUserDateLayout = new QHBoxLayout();
    this->pPostBodyLayout = new QVBoxLayout();
    this->pVisibilityLayout = new QHBoxLayout();

    this->pUsernameLabel = new QLabel(userWhoPosts.c_str(),this);
    this->pDateLabel = new QLabel(dateOfPost.c_str(),this);
    this->pPostTextLabel = new QLabel(textOfPost.c_str(),this);

    this->visibility = PostWidget::pVisibleToText ;
    switch(stoi(visibleToWhom))
    {
        case 0:
            this->visibility += " Everyone";
            break;
        case 1:
            this->visibility += " Friends";
            break;
        case 2:
            this->visibility += " Close Friends";
            break;
        case 3:
            this->visibility += " Acquaintances";
            break;
    }
    this->pVisibleToLabel = new QLabel (this->visibility.c_str(), this);
    if(isOwnerOfPost)
    {
        this->pDeletePostButton = new QPushButton(PostWidget::pDeletePostButtonText, this);
        connect(this->pDeletePostButton, &QPushButton::clicked, this, &PostWidget::onRemoveClick);
        connect(this, SIGNAL(remove(int)), this->parent(), SLOT(removePost(int)));
    }

    /*this->pMainLayout ->(
            "QLabel {"
            "background-color: #e8e8e8;"
            "border-style: hidden;"
            "border-radius: 8px;"
            "border-width: 1px;"
            "padding: 3px;"
            "color :  #1d1817; "
            "}"
            );*/
    this->pUsernameLabel->show();
}

void PostWidget::settleLayouts() {
    this->setLayout(this->pMainLayout);

    this->pMainLayout ->addItem(this->pUserDateLayout);
    this->pMainLayout ->addItem(this->pPostBodyLayout);
    this->pMainLayout ->addItem(this->pVisibilityLayout);
    if(isOwnerOfPost)
        this->pMainLayout ->addWidget(this->pDeletePostButton);

    this->pUserDateLayout ->addWidget(this->pUsernameLabel);
    this->pUserDateLayout ->addWidget(this->pDateLabel);

    this->pPostBodyLayout->addWidget(this->pPostTextLabel);

    this->pVisibilityLayout->addWidget(this->pVisibleToLabel);

    this->pMainLayout->setAlignment(Qt::AlignLeft);
    this->pPostTextLabel->setWordWrap(true);
}

void PostWidget::onRemoveClick() {
    emit remove(this->postID);
}
