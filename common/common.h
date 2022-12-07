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

        REQUEST_CREATE_ACCOUNT  = 305,

        //refresh la lista de useri
        REQUEST_REFRESH_USERS = 310,

        REQUEST_GET_CHAR = 315,

        REQUEST_WRITE_MESSAGE = 320,

        REQUEST_NEW_POST = 330,

        REQUEST_ADD_FRIEND = 335

    };

    enum ServerResponse : int{
        LOGIN_SUCCESS = 200,

        LOGIN_BAD_USER_PASS = 400,

        LOGIN_USER_ALREADY_CONNECTED = 401,

        CREATE_ACCOUNT_USERNAME_EXISTS = 402,

        //cand apesi pe login desi nu esti logat
        ACCES_DENIED_NOT_LOGGED_IN = 403
    };


    constexpr static const char * LOCALHOST = "127.0.0.1";
    constexpr static ushort SERVER_PORT = 56000;
    constexpr static const char * SERVER_IP = LOCALHOST;


    static void writeBuffer(int fd,  char * pBuf){
        int bufLen = strlen(pBuf);
        write(fd, & bufLen, 4);
        write(fd, pBuf, bufLen);
    }

    static void readBuffer(int fd, void * pBuf){

        memset(pBuf, 0, BUFFER_LENGTH);
        int bufLen;
        int retVal = read(fd, & bufLen, 4);
        read(fd, pBuf, bufLen);
    }
    static void readBufferInt(int fd, int & pBuf){

        if(read(fd, &pBuf, sizeof(int) == -1))
            //aruncam o eroare
            printf("eroare la readint\n");
    }

};


#endif //QT1_COMMON_H
