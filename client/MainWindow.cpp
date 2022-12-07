//
// Created by mirunasav on 29.11.2022.
//

#include "MainWindow.h"
#include <QMainWindow>
#include "LoginWidget.h"
#include "AppHomeWidget.h"
#include "../NotLoggedIn.h"

uint MainWindow::WIDTH = 1280;
uint MainWindow::HEIGHT = 720;
char const * MainWindow::pWindowTitle = "VirtualSoc";

MainWindow:: MainWindow (QWidget *parent) :
        QWidget(parent) {

    this->initWindow();
}

void MainWindow :: initWindow(){
    this->resize(MainWindow :: WIDTH, MainWindow ::HEIGHT);

    this->pCentralWidget = new LoginWidget ( this );
    this->pMainLayout = new QVBoxLayout();
    this->setLayout(pMainLayout);
    pMainLayout->addWidget(pCentralWidget);
    this->setWindowTitle(pWindowTitle);

}

void MainWindow::swapWidgetsLoginSuccess() {
    QWidget* pOldWidget = this->pCentralWidget; //retin widgetul activ
    this->pCentralWidget = new AppHomeWidget(this);//setez un home widget ca activ

    //in loc de setCentralWidget
//    this->pLayout = new QVBoxLayout();
//    this->setLayout(pLayout);
    this->pMainLayout->removeWidget(pOldWidget);
    pMainLayout->addWidget(pCentralWidget);//activez widgetul

    pOldWidget->hide();
    delete pOldWidget;

}

void MainWindow ::swapWidgetsUserDisconnect() {

    QWidget* pOldWidget = this->pCentralWidget; //retin widgetul activ
    this->pCentralWidget = new LoginWidget(this);//setez un feed widget ca ativ

    //in loc de setCentralWidget
    this->pMainLayout = new QVBoxLayout();
    this->setLayout(pMainLayout);
    pMainLayout->addWidget(pCentralWidget);//activez widgetul

    //pe urma tb sa fac ceva aici ca sa deconectez userul
    /*...*/

    this->setWindowTitle(MainWindow:: pWindowTitle);

    pOldWidget->hide();
    delete pOldWidget;



}


void MainWindow::swapWidgetsSkip() {
    QWidget* pOldWidget = this->pCentralWidget; //retin widgetul activ
    this->pCentralWidget = new NotLoggedIn(this);//setez un home widget ca activ

    //in loc de setCentralWidget
//    this->pLayout = new QVBoxLayout();
//    this->setLayout(pLayout);
    this->pMainLayout->removeWidget(pOldWidget);
    pMainLayout->addWidget(pCentralWidget);//activez widgetul

    pOldWidget->hide();
    delete pOldWidget;
}


MainWindow :: ~MainWindow () {
    //poate mai modific ceva in fisierele serverului aici idk vedem

}


