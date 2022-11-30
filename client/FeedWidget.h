//
// Created by loghin on 01/12/22.
//

#ifndef QT1_FEEDWIDGET_H
#define QT1_FEEDWIDGET_H


#include "MainWindow.h"
#include <QWidget>


class FeedWidget : public QWidget{
private:
    MainWindow * pParent{ nullptr };

public:
   explicit FeedWidget(MainWindow *);
};


#endif //QT1_FEEDWIDGET_H
