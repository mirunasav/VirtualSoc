#include <QApplication>
#include <QPushButton>
#include "LogInInterface/MainWindow.h"
#include <QApplication>
#include "ServerConnection.h"
#include "../common/common.h"

int main (int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    w.resize(1024, 768);
    return app.exec();
   /*ServerConnection :: getInstance().connect(common::SERVER_IP, common::SERVER_PORT);

   if(!ServerConnection::getInstance().isConnected())
   {
       printf("conexiune esuata\n");
   }

   char msg[100];
  strcpy(msg, "lala");
    common::writeBuffer(ServerConnection::getInstance().getSocket(), msg);
    printf("am scris mesajul\n");

*/

}
