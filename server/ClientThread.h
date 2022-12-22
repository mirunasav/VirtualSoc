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
    //id ul threadului alocat
    pthread_t ID;

    //canalul de comunicare

    Socket clientSocket;

    int ServerResponseInt;

    bool loggedIn {false};
public:
    //constructorul fara parametri nu poate fi apelat
    ClientThread( ) = delete;


    //primeste de la server thread id ul
    explicit ClientThread (pthread_t threadID);

    //obtine socketul de comunicare
    void acquireSocketFromServer () ;

    void main();//mainul threadului

    //treat requests o sa le fac intr un request handler mai incolo;

    int treatRequest(common::ClientRequests);

    void treatSignUp() ;

    void treatLogout() ;

    void treatLogin();

    void treatAddFriends();




};


#endif //QT1_CLIENTTHREAD_H
