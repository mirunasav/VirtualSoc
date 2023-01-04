//
// Created by mrnk on 12/4/22.
//

#ifndef QT1_CLIENTTHREAD_H
#define QT1_CLIENTTHREAD_H
#include <pthread.h>
#include <string>
#include "../common/common.h"
//threadul alocat unui client conectat



class ClientThread {
private:

    //canalul de comunicare

    int ServerResponseInt;

public:
    //constructorul fara parametri nu poate fi apelat
    ClientThread( ) = delete;


    //primeste de la server thread id ul
    explicit ClientThread (pthread_t threadID, Socket );

    //obtine socketul de comunicare
    void acquireSocketFromServer () ;

    void main();//mainul threadului

    void disconnectThread() const;

    Socket clientSocket;
    //id ul threadului alocat
    pthread_t ID;
    bool loggedIn {false};
    bool isPrivate {false};
};


#endif //QT1_CLIENTTHREAD_H
