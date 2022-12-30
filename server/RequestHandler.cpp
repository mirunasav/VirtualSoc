//
// Created by mrnk on 12/30/22.
//

#include "RequestHandler.h"
#include "../common/common.h"
#include "Server.h"
int RequestHandler::handleRequest( ClientThread  & client,  common::ClientRequests request) {
    RequestHandler::handleLoginRequest(client);
    return 200;
}

void RequestHandler::handleLoginRequest(ClientThread &client) {
    //verific daca nu sunt cumva in lista de useri deja conectati
    //verific daca usernameul si parola sunt in fisierul de useri
    std::string username = common::readString(client.clientSocket);
    std::string password = common::readString (client.clientSocket);

    //verificam daca userul nu e deja conectat
    for(const auto & connectedClientData : Server::getInstance().getClientThreadDataInstant())
    {
        if(!connectedClientData.username.empty() && connectedClientData.username==username){
            writeResponse(client.clientSocket,common:: ServerResponse :: LOGIN_USER_ALREADY_CONNECTED);
            return;
        }
    }

    //daca nu e conectat deja, verificam fisierul cu parole
    if(Server::getInstance().checkLogin(username, password, client.ID))
    {
        client.loggedIn = true;
        client.isPrivate = Server::getInstance().isPrivate(client.ID);
        writeResponse(client.clientSocket, common::ServerResponse::LOGIN_SUCCESS);
    }
    else
        writeResponse(client.clientSocket, common::ServerResponse::LOGIN_BAD_USER_PASS);
}

