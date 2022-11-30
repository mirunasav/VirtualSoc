#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"
#include <QApplication>

int main (int argc, char ** argv) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    w.resize(1024, 768);
    return app.exec();
}
