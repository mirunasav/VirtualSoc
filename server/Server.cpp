//
// Created by mrnk on 12/4/22.
//

#include "Server.h"
#include <sys/socket.h>
#include <stdexcept>
#include <unistd.h>
#include <list>

#include "ClientThread.h"

constexpr Socket INVALID_SOCKET =  (Socket) SOCKET_ERROR;

Server Server::instance;

//ma asigur ca doua threaduri nu acceseaza un fisier in acelasi timp
//blochez sectiuni de cod, un singur thread va fi in bucata
//dintre lock si unlock intr un singur moment

static pthread_mutex_t  threadListLock; // cand accesam lista de threaduri
static pthread_mutex_t  usersFileLock; // cand accesam usersFIle.txt pt login/sign up
static pthread_mutex_t  chatFileLock; //cand scriem/citim intr-un chat file
static pthread_mutex_t  feedFileLock;
//banuiesc ca o sa mai tb unul pt feed, pt cand scriem/citim din feed file?

//creez un socket nou

auto Server:: newSocket()
{
    Socket s;
    s = socket(AF_INET, SOCK_STREAM, PF_UNSPEC);

    if(s == INVALID_SOCKET)
        throw std::runtime_error("Failure at socket initialization!\n");
    return s;
}

auto Server::reuseAddress(Socket s) {
    int toggle = 1;

    if( -1 == setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &toggle, sizeof(int)))
        throw std::runtime_error ("Set reusable address error!\n");

    return s;
}

auto Server::bindSocket(Socket s, short port) {
    sockaddr_in serverAddressInformation {};
    serverAddressInformation.sin_addr.s_addr    = htonl ( INADDR_ANY );
    serverAddressInformation.sin_port           = htons ( port );
    serverAddressInformation.sin_family         = AF_INET;

    if ( SOCKET_ERROR == bind (
            s,
            reinterpret_cast < sockaddr * > ( & serverAddressInformation ),
            sizeof ( sockaddr_in )
    ) )
        throw std::runtime_error ( "Bind error" );
    return s;
}
\
//facem o coada de asteptare pt clienti
//pt cazul in care vor mai multi sa se conecteze fix in acelasi timp
//clientii din coada sunt acceptati pe rand

auto Server::listenSocket(Socket s, int queueSize) {

  if ( listen(s, queueSize ) == -1 ) //avem eroare
      throw std::runtime_error("Error at listen!\n");

  return s;
}

//o functie de tip initServer, cand facem setupul
//cream un nou socket
//setam optiunea de reuse address
// legam adresa de socket
//facem listen ca sa "auzim" daca gasim conexiuni

//initializam lacatele


Server &Server::setup(short port, int queueSize) {
    this->serverSocket = listenSocket(bindSocket(reuseAddress(newSocket()),port),queueSize);
    pthread_mutex_init ( & threadListLock, nullptr );
    pthread_mutex_init ( & usersFileLock, nullptr );
    pthread_mutex_init ( & chatFileLock, nullptr );
    pthread_mutex_init ( & feedFileLock, nullptr );

    return *this;
}


void *Server::clientThreadInit(void *pArg) {
  //
    ClientThread ( ( * ( pthread_t * ) pArg ) ).main();
    return nullptr;
}


void Server::run() {
    ConnectedClientData newClientData;
    socklen_t   clientAddressDataSize = sizeof ( newClientData );

    while(true)
    {
        if ( (newClientData.socket = accept (
                this->serverSocket,
                reinterpret_cast < sockaddr * > ( & newClientData.clientAddress ),
                & clientAddressDataSize
                )) == INVALID_SOCKET)
            continue ; //nu a reusit acceptul -> continui loopul

        newClientData.username.clear();
         //cream un thread nou, care isi salveaza id ul in newClientData.threadID
         //si are ca parametru acelasi threadID, dar modificat

         pthread_create(& newClientData.threadID, nullptr, clientThreadInit, & newClientData.threadID);
         this->addClientData(newClientData); //adaugam clientData(socket , threadID, username) la lista retinuta de server
    }

}


Server &Server::addClientData(const Server::ConnectedClientData & clientData) {
    pthread_mutex_lock(& threadListLock); //blochez accesul la lista

    this->clientList.push_front(clientData);

    pthread_mutex_unlock( & threadListLock ); // se deblocheaza accesul la lista
    return * this;
}

std::list<Server::ConnectedClientData> Server::getClientThreadDataInstant() const {
    //blochez accesul la lista
    pthread_mutex_lock( & threadListLock );
    //copiez toate elementele care se afla in acest moment in lista
    auto result = std::list < Server::ConnectedClientData > ( this->clientList.begin(), this->clientList.end() );

    //deblochez accestul

    pthread_mutex_unlock(&threadListLock);
    return result;

}

Socket Server::getClientSocket(pthread_t threadID) const {
    pthread_mutex_lock(&threadListLock);

    Socket s = INVALID_SOCKET;

    for(auto &clientData : this->clientList)
        if(clientData.threadID == threadID)
            s = clientData.socket;

    pthread_mutex_unlock(&threadListLock);

    return s;
}

bool Server::checkUser(std::string & username , std::string & password, pthread_t) {
    return false;
}
/*
Server &Server::disconnect(pthread_t threadID) {
    pthread_mutex_lock( & threadListLock );


    for (  auto & clientData : this->clientList )
        if ( clientData.threadID == threadID ) {
            close ( clientData.socket );
            this->clientList.remove( clientData );
            break;
        }

}*/

bool Server::createUser(std::string &, std::string &) {
    return false;
}



std::string Server::getClientUsername(pthread_t) {
    return std::string();
}


