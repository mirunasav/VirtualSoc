//
// Created by loghin on 01/12/22.
//

#ifndef QT1_FEEDWIDGET_H
#define QT1_FEEDWIDGET_H


#include "MainWindow.h"
#include <QWidget>


class FeedWidget : public QWidget{
Q_OBJECT
private:
    MainWindow *pParent {nullptr};

    QLayout *pLayout {nullptr};
public:
    explicit FeedWidget(MainWindow *pParentWindow);
    void initWidget();
    void createComponents();
    void settleComponents();



};



#endif //QT1_FEEDWIDGET_H
