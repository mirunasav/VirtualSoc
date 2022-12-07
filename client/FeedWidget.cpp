//
// Created by mrnk on 12/2/22.
//

#include <QVBoxLayout>
#include "FeedWidget.h"
FeedWidget:: FeedWidget(QWidget *pParentWindow):
        QWidget(pParentWindow){
    this->initWidget();

}
void FeedWidget::initWidget()
{
   QPalette pal = QPalette();
   pal.setColor(QPalette::Window, Qt::white);
   this->setAutoFillBackground(true);
   this->setPalette(pal);
   this->show();
   createComponents();
   settleLayouts();
}
void FeedWidget::createComponents()
{
    this->pLayout = new QVBoxLayout(this);

}
void FeedWidget::settleLayouts()
{
    this->setLayout(this->pLayout);


}
FeedWidget::~FeedWidget() = default;