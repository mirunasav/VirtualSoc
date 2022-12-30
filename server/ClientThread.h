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
    explicit ClientThread (pthread_t threadID);

    //obtine socketul de comunicare
    void acquireSocketFromServer () ;

    void main();//mainul threadului

    //treat requests o sa le fac intr un request handler mai incolo;

    int treatRequest(common::ClientRequests);

    std::string getClientUsername() const;

    void treatSignUp() ;

    void treatLogout() ;

    void treatLogin();

    void treatAddFriends();

    void treatGetFriendList();

    void treatGetNumberOfFriends();

    void treatRemoveFriend();

    void treatChangeFriendshipType();

    void treatGetPrivacyType();

    void treatChangePrivacyType(common::privacySetting);

    void treatGetChatFile(common::openMode);

    void treatGetAllChats();


    Socket clientSocket;
//id ul threadului alocat
pthread_t ID;
    bool loggedIn {false};
    bool isPrivate {false};
};


#endif //QT1_CLIENTTHREAD_H
