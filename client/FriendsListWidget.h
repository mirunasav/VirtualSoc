//
// Created by mrnk on 12/14/22.
//

#ifndef QT1_FRIENDSLISTWIDGET_H
#define QT1_FRIENDSLISTWIDGET_H


#include <QWidget>

class FriendsListWidget : public QWidget{
Q_OBJECT
private:
    QLayout *pLayout{nullptr};
public:
    explicit FriendsListWidget(QWidget *pParentWindow);
    void initWidget();
    void createComponents();
    void settleLayouts();
    ~FriendsListWidget() override = default;

};


#endif //QT1_FRIENDSLISTWIDGET_H
