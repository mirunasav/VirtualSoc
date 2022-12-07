//
// Created by mrnk on 12/4/22.
//

#include "ClientThread.h"
#include "Server.h"
#include "../common/common.h"
using namespace common;

bool ClientThread::checkUser(std::string & username,  std::string & password)  {
    return Server::getInstance().checkUser( username, password, this->ID );
}

ClientThread ::ClientThread(pthread_t threadID) :
            ID(threadID), clientSocket(Server::INVALID_SOCKET){

}

void ClientThread::acquireSocketFromServer() {
    this->clientSocket = Server::getInstance().getClientSocket( this->ID );
}

//in run :
//while : astept un request, il pasez la treatrequest;
void ClientThread::main() {
    while(this->clientSocket == Server::INVALID_SOCKET)
        this->acquireSocketFromServer();

    while(true)
    {
        //punem intr-un bloc de try si vom arunca exceptii in cas ca apar erori la read/write sau la conexiune
            readBufferInt(this->clientSocket,ServerResponseInt);
            this->treatRequest(static_cast <ClientRequests> (ServerResponseInt));

    }
    Server::getInstance().disconnect(this->ID);
}

void ClientThread::treatRequest(common::ClientRequests request) {
    switch ( request ) {
        case common::REQUEST_LOGIN:         return this->treatLogin ();

    }
}

void ClientThread::treatLogin() {
    //verific daca nu sunt cumva in lista de useri deja conectati
//verific daca usernameul si parola sunt in fisierul de useri

}



/*bool ClientThread::createUser(const std::string &, const std::string &) {
    return false;
}
*/