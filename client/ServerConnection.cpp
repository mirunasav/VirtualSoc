//
// Created by mrnk on 12/4/22.
//

#include "ServerConnection.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

ServerConnection ServerConnection::instance;

ServerConnection &ServerConnection::getInstance() {
    return ServerConnection :: instance;
}

bool ServerConnection :: connect (const char * pAddress, short port)
{
    if(this->connected)
        return true;
    //in caz de cv modific protocolul cu PF_UNSPEC

    this->clientSocket = socket(AF_INET, SOCK_STREAM,0);//domain, type, protocol

    sockaddr_in serverAddress { };
    serverAddress.sin_port = htons ( port );//portul ; htons: conversie a unui  short de la gazda la retea; host to network short
    serverAddress.sin_addr.s_addr = inet_addr( pAddress );//adresa IP
    serverAddress.sin_family = AF_INET;//familia de protocoale

    if(-1 == ::connect(this->clientSocket, reinterpret_cast < sockaddr * > ( & serverAddress ),
                       sizeof ( sockaddr_in )))
        return false;

   this->markAsConnected();

   return true;
}

bool ServerConnection::disconnect() {

    if (! this->connected) // e deconectat deja
        return false;
    close(this->clientSocket);
    this->connected = false;
    this->clientSocket = INVALID_SOCKET;
    return true;
}

void ServerConnection::markAsConnected() {
    this->connected = true;
}
