//
// Created by mrnk on 12/2/22.
//

#ifndef QT1_FEEDWIDGET_H
#define QT1_FEEDWIDGET_H


#include <QWidget>
#include <QPushButton>

class FeedWidget : public QWidget{
    Q_OBJECT
private:
    QLayout *pLayout{nullptr};

public:
    explicit FeedWidget(QWidget *pParentWindow);
    void initWidget();
    ~FeedWidget() override;
    void createComponents();
    void settleLayouts();

};


#endif //QT1_FEEDWIDGET_H
