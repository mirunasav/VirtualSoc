//
// Created by mirunasav on 29.11.2022.
//

#include "MainWindow.h"
#include <QMainWindow>

uint MainWindow::WIDTH = 1280;
uint MainWindow::HEIGHT = 720;

MainWindow:: MainWindow (QWidget *parent) :
        QWidget(parent) {

    this->initWindow();
}

void MainWindow :: initWindow(){
    this->resize(MainWindow :: WIDTH, MainWindow ::HEIGHT);

    //this->pCentralWidget = new LoginWidget(this);
//    this->setCentralWidget  (this->pCentralWidget);

    this->pMainLayout = new QVBoxLayout();
    this->setLayout(pMainLayout);

    this->pCentralWidget = new QWidget(this);
    pMainLayout->addWidget(pCentralWidget);

}

MainWindow :: ~MainWindow () {

}
