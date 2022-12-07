//
// Created by mrnk on 12/4/22.
//

#ifndef QT1_SERVER_H
#define QT1_SERVER_H

#include <pthread.h>
#include <netinet/in.h>
#include <string>
#include <list>
#include "../common/common.h"
class Server {
public:
    /* marimea maxima a cozii de asteptare a conectarilor clientilor
     * serverul accepta un singur client la o repetitie din bucla while, asa ca
     * foarte rar se paote intampla ca mai multi clienti sa vrea sa se conecteze fix in
     * acelasi timp. In acest caz, ii adaugam intr-o coada;
     **/
    constexpr static int DEFAULT_QUEUE_SIZE = 1024;

    struct ConnectedClientData   {
        //id-ul de thread

        pthread_t threadID;

        //id-ul userului
        std::string username;

        //adresa userului
        sockaddr_in clientAddress;

        Socket socket;

    };

    static constexpr Socket INVALID_SOCKET =  (Socket) SOCKET_ERROR;

private:
    //constructor default si privat, nu vrem sa construim de oriunde,
    //ci doar intern si sa-l dam mai departe cu getInstance();

    Server () noexcept = default;
    //instanta a serverului
    static Server instance;

    //lista cu toate datele threadurilor
    std::list <ConnectedClientData> clientList;

    Socket serverSocket {(Socket) SOCKET_ERROR}; //invalid socket
public:
    //cream un nou socket
    static auto newSocket();

    //cream functionalitatea reuse address
    static auto reuseAddress(Socket s);

    //leg socketul de ip address
    static auto bindSocket(Socket s, short port);

    static auto listenSocket(Socket s, int queueSize);

    //functie care creaza un nou clientThread, ii dam drept parametru
    //id ul threadului, pe care il luam din pArg
    static void *clientThreadInit(void * pArg);

    static Server & getInstance () {
        return Server::instance;
    }

    //verificam daca am primit un user si o parola valide;
    //daca sunt ok, ne tb si threadul ; salvam datele userului

    bool checkUser(std::string &, std:: string &, pthread_t);

    bool createUser(std::string &, std:: string &);

    //deconectam de la threadul respectiv clientul
    //returneaza referinta, in caz ca vrem sa folosim intr-o comanda inlantuita
    Server &disconnect (pthread_t);

    Server & addClientData (const ConnectedClientData &);

    //returnam o copie a structurilor care se exista intr un anumit moment
    //se modifica, constant
    std::list <ConnectedClientData> getClientThreadDataInstant () const;

    Socket getClientSocket(pthread_t) const;

    std::string getClientUsername(pthread_t);

    Server &setup (short, int = Server ::DEFAULT_QUEUE_SIZE);

    void run();

}
;

#endif //QT1_SERVER_H