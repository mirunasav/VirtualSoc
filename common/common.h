//
// Created by mrnk on 12/4/22.
//

#ifndef QT1_COMMON_H
#define QT1_COMMON_H

#include <string>
#include <cstring>
#include <unistd.h>

#define BUFFER_LENGTH 256
typedef int Socket;
constexpr int SOCKET_ERROR = -1;

namespace common {

    enum ClientRequests : int
    {
        //cand vrem sa facem login
        REQUEST_LOGIN = 300,

        REQUEST_SIGN_UP  = 305,

        //refresh la lista de useri
        REQUEST_REFRESH_USERS = 310,

        REQUEST_GET_CHAR = 315,

        REQUEST_WRITE_MESSAGE = 320,

        REQUEST_NEW_POST = 330,

        REQUEST_ADD_FRIEND = 335,

        REQUEST_LOGOUT = 340,

        NO_REQUEST = 400

    };

    enum ServerResponse : int{
        LOGIN_SUCCESS = 200,

        LOGIN_BAD_USER_PASS = 400,

        LOGIN_USER_ALREADY_CONNECTED = 401,

        CREATE_ACCOUNT_USERNAME_EXISTS = 402,

        CREATE_ACCOUNT_SUCCESS = 403,

        //cand apesi pe login desi nu esti logat
        ACCES_DENIED_NOT_LOGGED_IN = 404
    };


    constexpr static const char * LOCALHOST = "127.0.0.1";
    constexpr static ushort SERVER_PORT = 56000;
    constexpr static const char * SERVER_IP = LOCALHOST;

    constexpr static int READ_ERROR = -1;
    constexpr static int DISCONNECT = -2;
    constexpr static int WRITE_ERROR = -3;


    ClientRequests readRequest(Socket socket);
    ServerResponse readResponse (Socket socket);
    std::string readString(Socket socket );
    void readBuffer(int fd, void * pBuf);
    int readBufferInt(int fd, int & pBuf);

    void writeBuffer(int fd,  char * pBuf);
    void writeRequestNumber(Socket socket, int requestNumber);
    void writeRequest ( Socket socket, ClientRequests request);
    void writeString (Socket socket, const std::string &message);
    void writeResponse (Socket , ServerResponse );

};


#endif //QT1_COMMON_H
