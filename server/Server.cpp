//
// Created by mrnk on 12/4/22.
//

#include "Server.h"
#include <sys/socket.h>
#include <stdexcept>
#include <unistd.h>
#include <list>
#include <fstream>
#include <iostream>

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
static pthread_mutex_t  friendsFileLock;
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

bool Server::checkLogin(std::string & username , std::string & password, pthread_t requestThreadID) {
    pthread_mutex_lock(&usersFileLock);

    std::ifstream usersFile;
    usersFile.open(Server::pUsersFile);

    std::string usernameFromFile, passwordFromFile;

    while (usersFile >>usernameFromFile >>passwordFromFile)
    {
        if(username == usernameFromFile && password == passwordFromFile) { //scriu in connectedClientData
            this->writeToConnectedClientData(username, requestThreadID);
            pthread_mutex_unlock(&usersFileLock);
            usersFile.close();
            return true;
        }

    }

    pthread_mutex_unlock(&usersFileLock);
    usersFile.close();
    return false;
}
bool Server::checkUserExists(std::string & username) {
    pthread_mutex_lock(&usersFileLock);

    std::ifstream usersFile;
    usersFile.open(Server::pUsersFile);

    std::string usernameFromFile, passwordFromFile;
     while (usersFile >>usernameFromFile >>passwordFromFile)
    {
        if(username == usernameFromFile )
        {

            pthread_mutex_unlock(&usersFileLock);
            usersFile.close();
            return true;
        }

    }

    pthread_mutex_unlock(&usersFileLock);
    usersFile.close();
    return false;
}


std::string Server::getUsername(pthread_t ID) const{
    pthread_mutex_lock ( & threadListLock );

    std::string username = "none"; // o valoare default
    for ( const auto & clientData : this->clientList)
        if ( clientData.threadID == ID ) { // cautam username-ul thread-ului cu ID-ul dat
            username = clientData.username;
            break;
        }

    pthread_mutex_unlock( & threadListLock );

    return username;
}

bool Server::createUser( std::string &username,  std::string &password, pthread_t requestThreadID) {
    pthread_mutex_lock(&usersFileLock);

    std::fstream usersFile;
    usersFile.open(Server::pUsersFile);

    std::string usernameFromFile, passwordFromFile;

    while (usersFile >>usernameFromFile >>passwordFromFile)
    {
        if(usernameFromFile == username) //daca exista deja un username la fel
        {
            pthread_mutex_unlock( & usersFileLock );
            usersFile.close();
            return false;
        }
    }

    usersFile.close();

    usersFile.open(Server::pUsersFile ,  std::iostream::app);

    usersFile << username.c_str() <<' ' << password.c_str() << '\n';
    pthread_mutex_unlock( & usersFileLock );
    usersFile.close();
    this->writeToConnectedClientData(username, requestThreadID);
    return true;
}
std::string Server::createFriendListFileName(std::string &username) {
    auto userFriendListFile =  std::string(Server::pFriendListFiles)
            .append("/")
            .append( username)
            .append("_")
            .append("Friends")
            .append( ".txt" );
    return userFriendListFile;
}

bool Server::addFriend(std::string &requesterUsername, std::string &usernameAdded) {
    pthread_mutex_lock(&friendsFileLock);

 auto requesterFriendListFile = createFriendListFileName(requesterUsername);

    auto otherFriendListFile =  createFriendListFileName(usernameAdded);

 std::fstream friendListFile;
 //mai intai verific daca nu cumva il am deja ca
 //deschid fisierul normal, fara sa pot scrie in el
 friendListFile.open(requesterFriendListFile);
 std::string usernameFromFile, friendshipType; //1->normal, 2->close friend, 3->cunostinta

    while (friendListFile >> usernameFromFile >> friendshipType)
    {
        if(usernameFromFile == usernameAdded) { //e deja in lista
            friendListFile.close();
            return false;
        }
    }
    //daca nu l-am gasit, deschid fisierul cu append si il adaug
    friendListFile.close();
    friendListFile.open(requesterFriendListFile, std::iostream::app);
    friendListFile << usernameAdded.c_str()<<' '<<common::typesOfFriend ::NORMAL_FRIEND <<'\n';
    friendListFile.close();

    //deschid si fisierul de prieteni al prietenului tocmai adaugat, si adaug
    //usernameul celui care a dat request

    friendListFile.open(otherFriendListFile, std::iostream::app);
    friendListFile <<requesterUsername.c_str()<<' '<<std::to_string(common::typesOfFriend ::NORMAL_FRIEND ).c_str()<<'\n';
    friendListFile.close();
    pthread_mutex_unlock(&friendsFileLock);
    return true;
}
std::fstream & Server::getFriendListFile(std::string &username) {
    pthread_mutex_lock(&friendsFileLock);

    auto friendsFileName = createFriendListFileName(username);
    this->currentOpenFriendFile.open(friendsFileName, std::fstream::in);

    return this->currentOpenFriendFile;
}

int Server::getNumberOfFriends(std::string &username) {
    pthread_mutex_lock(&friendsFileLock);
    auto friendsFileName = createFriendListFileName(username);
    std::fstream friendListFile;
    int numberOfFriends = 0;
    std::string usernameFromFile, typeOfFriendship;

    friendListFile.open(friendsFileName, std::fstream::in);
    while(friendListFile>>usernameFromFile>>typeOfFriendship)
        numberOfFriends++;

    friendListFile.close();
    pthread_mutex_unlock(&friendsFileLock);
    return numberOfFriends;

}
void Server::changeFriendshipType(std::string & requesterUsername, std::string &friendUsername, std::string &newFriendshipType) {
    pthread_mutex_lock(&friendsFileLock);

    auto friendFileName = this->createFriendListFileName(requesterUsername);
    std::fstream friendFile ;

    std::fstream newFriendFile;
    std::string newFileName = "new";//nu o sa ramana asa

    friendFile.open(friendFileName, std::fstream::in);
    //creez un fisier intermediar in care copiez toate liniile
    newFriendFile.open("new", std::fstream::app);

    std::string usernameFromFile, typeFromFile;
    while(friendFile>>usernameFromFile>>typeFromFile)
    {
        if(usernameFromFile == friendUsername)
            newFriendFile << usernameFromFile.c_str() <<' ' << newFriendshipType.c_str() << '\n';
        else
            newFriendFile << usernameFromFile.c_str() <<' ' << typeFromFile.c_str() << '\n';
    }

    friendFile.close();
    newFriendFile.close();
    std::remove(friendFileName.c_str());
    std::rename("new", friendFileName.c_str());

    pthread_mutex_unlock(&friendsFileLock);

}

void Server::removeFriendFromBothLists(std::string &requesterUsername, std::string & usernameToRemove) {
    //sterg 1 din lista lui 2 si 2 din lista lui 1
    this->removeFriendFromOneList(requesterUsername, usernameToRemove);
    this->removeFriendFromOneList(usernameToRemove, requesterUsername);
}
void Server::removeFriendFromOneList(std::string &requesterUsername, std::string & usernameToRemove) {
    pthread_mutex_lock(&friendsFileLock);

    auto friendFileName = this->createFriendListFileName(requesterUsername);
    std::fstream friendFile ;

    std::fstream newFriendFile;
    std::string newFileName = "new";//nu o sa ramana asa

    friendFile.open(friendFileName, std::fstream::in);
    //creez un fisier intermediar in care copiez toate liniile
    newFriendFile.open("new", std::fstream::app);

    std::string usernameFromFile, typeFromFile;
    while(friendFile>>usernameFromFile>>typeFromFile)
    {
        if(usernameFromFile != usernameToRemove)
             newFriendFile << usernameFromFile.c_str() <<' ' << typeFromFile.c_str() << '\n';
    }

    friendFile.close();
    newFriendFile.close();
    std::remove(friendFileName.c_str());
    std::rename("new", friendFileName.c_str());

    pthread_mutex_unlock(&friendsFileLock);

}

void Server::releaseFile(int type) {
    switch(type)
    {
        case 1: //friendFile
             this->currentOpenFriendFile.close();
            pthread_mutex_unlock(&friendsFileLock);
            return;
        case 2://chatFile
            this->currentOpenChatFile.close();
            pthread_mutex_unlock(&chatFileLock);
            return;
    }
}

Server &Server::disconnect(pthread_t threadID) {
   this->logout(threadID);

}

//scoatem clientul din lista, dar nu inchidem socketul
Server &Server::logout(pthread_t threadID) {
    pthread_mutex_lock( & threadListLock );


    for (  const auto & clientData : this->clientList )
        if ( clientData.threadID == threadID ) {
            this->clientList.remove( clientData );
            break;
        }

    pthread_mutex_unlock(&threadListLock);

    return *this;
}

void Server::writeToConnectedClientData(std::string username, pthread_t requestThreadID)
{
    pthread_mutex_lock(&threadListLock); //blocam lista de threaduri

    for (auto & clientData : this->clientList)
    {
        if(clientData.threadID == requestThreadID)
            clientData.username = username;
    }
    pthread_mutex_unlock(&threadListLock);
}



bool Server::ConnectedClientData::operator==(const Server::ConnectedClientData &other) const {
    return this->threadID == other.threadID;
}
