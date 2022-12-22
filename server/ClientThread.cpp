//
// Created by mrnk on 12/4/22.
//

#include "ClientThread.h"
#include "Server.h"
#include "../common/common.h"
using namespace common;

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

    int status_code = 0;
    while(status_code != 499)
    {
        //punem intr-un bloc de try si vom arunca exceptii in cas ca apar erori la read/write sau la conexiune
        status_code = this->treatRequest(common::readRequest(this->clientSocket));

    }
    Server::getInstance().disconnect(this->ID);
}

int ClientThread::treatRequest(common::ClientRequests request) {
    switch ( request ) {
        case common::REQUEST_LOGIN:
            this->treatLogin ();
            return 200;

        case common::REQUEST_SIGN_UP:
            this->treatSignUp();
            return 200;
        case common::REQUEST_ADD_FRIEND:
            this->treatAddFriends();
            return 200;

            //cand se inchide clientul din x / neasteptat, nu din butonul de logout
        case common::NO_REQUEST :
            Server::getInstance().disconnect(this->ID);
            return 499;

            //cand inchid clientul din butonul de logout:
        case common::REQUEST_LOGOUT:
            this->treatLogout();
            this->loggedIn = false;
            return 401;


    }
}

void ClientThread::treatLogin() {
    //verific daca nu sunt cumva in lista de useri deja conectati
    //verific daca usernameul si parola sunt in fisierul de useri
    std::string username = common::readString(this->clientSocket);
    std::string password = common::readString (this->clientSocket);

    //verificam daca userul nu e deja conectat
    for(const auto & connectedClientData : Server::getInstance().getClientThreadDataInstant())
    {
        if(!connectedClientData.username.empty() && connectedClientData.username==username){
            writeResponse(this->clientSocket,common:: ServerResponse :: LOGIN_USER_ALREADY_CONNECTED);
            return;
        }
    }

    //daca nu e conectat deja, verificam fisierul cu parole
    if(Server::getInstance().checkLogin(username, password, this->ID))
    {
        this->loggedIn = true;
        writeResponse(this->clientSocket, common::ServerResponse::LOGIN_SUCCESS);
    }
    else
     writeResponse(this->clientSocket, common::ServerResponse::LOGIN_BAD_USER_PASS);
}


void ClientThread::treatSignUp()  {
    std::string username = common::readString(this->clientSocket);
    std::string password = common::readString (this->clientSocket);

    if(Server::getInstance().createUser(username, password)) //daca a reusit crearea
    {
        writeResponse(this->clientSocket, common::ServerResponse::CREATE_ACCOUNT_SUCCESS);
        this->loggedIn = true;
    }
    else
        writeResponse(this->clientSocket, common::ServerResponse::CREATE_ACCOUNT_USERNAME_EXISTS);

}

void ClientThread::treatLogout()  {
    Server::getInstance().logout(this->ID);
    this->loggedIn = false;
}

void ClientThread::treatAddFriends() {
    std::string username = common::readString(this->clientSocket);

    //daca usernameul introdus e chiar al celui care trimite cererea
    for(const auto & connectedClientData : Server::getInstance().getClientThreadDataInstant())
    {
        if(!connectedClientData.username.empty() && connectedClientData.username==username && connectedClientData.threadID == this->ID){
            writeResponse(this->clientSocket,common:: ServerResponse :: ADD_FRIENDS_OWN_USERNAME);
            return;
        }
    }

    if(Server::getInstance().checkUserExists(username)) {
        auto requesterUsername =Server::getInstance().getUsername(this->ID);

       if( Server::getInstance().addFriend(requesterUsername, username))
           writeResponse(this->clientSocket, common::ServerResponse::ADD_FRIENDS_REQUEST_SENT);
       else
           writeResponse(this->clientSocket, common::ServerResponse::ADD_FRIENDS_ALREADY_FRIEND);

    }
    else
        writeResponse(this->clientSocket, common::ServerResponse::ADD_FRIENDS_INVALID_USER);

}







/*bool ClientThread::createUser(const std::string &, const std::string &) {
    return false;
}
*/