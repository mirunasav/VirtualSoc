//
// Created by mirunasav on 29.11.2022.
//

#include "MainWindow.h"
#include <QMainWindow>
#include <QMessageBox>
#include "LoginWidget.h"
#include "../InApp/AppHomeWidget.h"
#include "../InApp/NotNormalUser.h"
#include "../ServerConnection.h"

int MainWindow::WIDTH = 1280;
int MainWindow::HEIGHT = 720;
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

    this->setWindowTitle(MainWindow:: pWindowTitle);

    pOldWidget->hide();
    delete pOldWidget;



}

void MainWindow::swapWidgetsSkip() {
    QWidget* pOldWidget = this->pCentralWidget; //retin widgetul activ

    ServerConnection::getInstance().connect(common::SERVER_IP, common::SERVER_PORT);

    if(!ServerConnection::getInstance().isConnected()) //nu a mers conexiunea
    {
        this->notificationPopUp(LoginWidget::pServerDown);
        return;
    }

    this->pCentralWidget = new NotNormalUser(this,false);//setez un home widget ca activ

    //in loc de setCentralWidget
//    this->pLayout = new QVBoxLayout();
//    this->setLayout(pLayout);
    this->pMainLayout->removeWidget(pOldWidget);
    pMainLayout->addWidget(pCentralWidget);//activez widgetul

    pOldWidget->hide();
    delete pOldWidget;
}

void MainWindow::notificationPopUp(const char *message) {
    //apare un text box pop up; parintele este this
    //titlul este ..., mesajul este message, un buton de ok
    QMessageBox::information(this, " ", message,QMessageBox::Ok);

}

MainWindow :: ~MainWindow () {
    //poate mai modific ceva in fisierele serverului aici idk vedem

}

void MainWindow::swapWidgetsAdmin() {
    QWidget* pOldWidget = this->pCentralWidget; //retin widgetul activ
    this->pCentralWidget = new NotNormalUser(this,true);//setez un home widget ca activ

    //in loc de setCentralWidget
//    this->pLayout = new QVBoxLayout();
//    this->setLayout(pLayout);
    this->pMainLayout->removeWidget(pOldWidget);
    pMainLayout->addWidget(pCentralWidget);//activez widgetul

    pOldWidget->hide();
    delete pOldWidget;
}


