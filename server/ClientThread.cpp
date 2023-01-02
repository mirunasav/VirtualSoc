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

void ClientThread::acquireSocketFromServer() {
    this->clientSocket = Server::getInstance().getClientSocket( this->ID );
}

//in run :
//while : astept un request, il pasez la requestHandler;
void ClientThread::main() {
   // while(this->clientSocket == Server::INVALID_SOCKET)
     //   this->acquireSocketFromServer();

    int status_code = 0;
    while(status_code != 499)
    {
        //punem intr-un bloc de try si vom arunca exceptii in cas ca apar erori la read/write sau la conexiune
        //status_code = this->treatRequest(common::readRequest(this->clientSocket));
        status_code = RequestHandler::handleRequest(* this, common::readRequest(this->clientSocket));

    }
    Server::getInstance().disconnect(this->ID);
}
