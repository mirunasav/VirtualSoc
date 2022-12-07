//
// Created by mirunasav on 29.11.2022.
//

#ifndef QT1_MAINWINDOW_H
#define QT1_MAINWINDOW_H


#include <QVBoxLayout>
#include <QWidget>
#include "LoginWidget.h"
//construiesc fereastra mare si fac swap intre login si aplicatie
//fac evenimentele 'swapWidgetsLoginSuccess' si 'swapWidgetsUserDisconnect'
//pCentral widget are widgetul activ

class MainWindow : public QWidget {
    Q_OBJECT

public slots:
    //slot : function that is called in response to a particular signal
    void swapWidgetsLoginSuccess();
    void swapWidgetsUserDisconnect();
    void swapWidgetsSkip();


public:
    static char const * pWindowTitle;

    static uint WIDTH ;
    static uint HEIGHT;

    explicit MainWindow (QWidget * parent = nullptr);

    //distruge widgetul activ
    ~MainWindow () override;

private:
    QLayout * pMainLayout {nullptr};
    QWidget * pCentralWidget {nullptr};

    void initWindow(); //construieste fereastra si widgetul de la inceput
};

#endif //QT1_MAINWINDOW_H
