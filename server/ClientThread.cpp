//
// Created by mrnk on 12/4/22.
//

#include <fstream>
#include "ClientThread.h"
#include "Server.h"
#include "../common/common.h"
#include "RequestHandler.h"
using namespace common;

ClientThread ::ClientThread(pthread_t threadID, Socket clientSocket) :
            ID(threadID), clientSocket(clientSocket){

}

//in run :
//while : astept un request, il pasez la requestHandler;
void ClientThread::main() {
   // while(this->clientSocket == Server::INVALID_SOCKET)
     //   this->acquireSocketFromServer();

    int status_code = 0;
    while(status_code != 499)
    {
            status_code = RequestHandler::handleRequest(* this, common::readRequest(this->clientSocket));
        //pot pune intr-un bloc de try si vom arunca exceptii in cas ca apar erori la read/write sau la conexiune

    }
    this->disconnectThread();
}

void ClientThread::disconnectThread() const {
    Server::getInstance().disconnect(this->ID);
}
