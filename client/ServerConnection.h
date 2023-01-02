//
// Created by mrnk on 12/4/22.
//

#ifndef QT1_SERVERCONNECTION_H
#define QT1_SERVERCONNECTION_H
#include "../common/common.h"


class ServerConnection {
private:
    //socketul prin care comunicam
    Socket clientSocket {(Socket ) SOCKET_ERROR};

    bool connected{false};

    //instanta conexiunii
    static ServerConnection instance;

    //constructorul e privat ca sa nu poate construi userul obiecte
    //de tipul asta, doar foloseste instanta

    static constexpr Socket INVALID_SOCKET =  (Socket) SOCKET_ERROR;

public:
    ServerConnection() = default;
    static ServerConnection &getInstance();

    constexpr bool isConnected() const {
        return this->connected;
    }

    //incearca sa se conecteze la un ip si un port (ale serverului)
    //returneaza true/false in functie de succes
    bool connect(const char *, short);

    bool disconnect();

    constexpr Socket getSocket() const
    {
        return this->clientSocket;
    }
};


#endif //QT1_SERVERCONNECTION_H
