//
// Created by mrnk on 12/4/22.
//

#ifndef QT1_SERVER_H
#define QT1_SERVER_H

#include <pthread.h>
#include <netinet/in.h>
#include <string>
#include <list>
#include <fstream>
#include <vector>
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

        //tip de privacy:
        common::privacySetting privacy;

        //adresa userului
        sockaddr_in clientAddress;

        Socket socket;
        bool operator == ( const Server::ConnectedClientData & ) const ;

    };


    static constexpr Socket INVALID_SOCKET =  (Socket) SOCKET_ERROR;

private:
    //constructor default si privat, nu vrem sa construim de oriunde,
    //ci doar intern si sa-l dam mai departe cu getInstance();
    constexpr static const char * pUsersFile = "../server/users.txt";
    constexpr static const char * pFriendListFiles= "../server/friend_files";
    constexpr static const char * pFriendRequestsFiles= "../server/request_files";
    constexpr static const char * pAllChatsFile= "../server/chat_files/all_chats.txt";
    constexpr static const char * pChatsPath= "../server/chat_files/";
    constexpr static const char * pPostsJSONPath= "../server/posts/all_posts.json";
    constexpr static const char * pBlockedUsersFiles= "../server/blocked_users_files";

    Server () noexcept = default;
    //instanta a serverului
    static Server instance;

    //lista cu toate datele threadurilor
    std::list <ConnectedClientData> clientList;

    Socket serverSocket {(Socket) SOCKET_ERROR}; //invalid socket

    std::fstream currentOpenFriendFile;
    std::fstream currentOpenFriendRequestsFile;
    std::fstream currentOpenChatFile;
    std::fstream currentOpenAllChatsFile;
    std::fstream currentOpenAllPostsJson;
    std::fstream currentOpenBlockedUsersFile;




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

    //functions for Login / SignUp:
    bool checkLogin(std::string &, std:: string &, pthread_t);

    bool createUser( std::string &,  std:: string &, pthread_t);

    static bool checkUserExists( std::string &);


    //functions for Friends:
    static void addFriend(std::string &, std::string &);

    static void blockUser(std::string &, std::string &);

    static void unblockUser(std::string &, std::string &);

    void removeFriendFromOneList(std::string &, std::string &);

    void removeFriendFromBothLists(std::string &, std::string &);

    static void removeFriendRequest (std::string &, std::string &);

    void changeFriendshipType(std::string &,std::string &, std::string &);

    static std::string createFriendListFileName (std::string &);

    static std::string createFriendRequestsFileName (std::string &);\

    static std::string createBlockedUsersFileName (std::string &);

    bool isFriend(std::string&, std::string &);

    bool isBlocked(std::string&, std::string &);

    std::fstream & getFriendListFile( std::string &);

    std::fstream & getFriendRequestsFile( std::string &);

    std::fstream & getBlockedUsersFile( std::string &);

    static int getNumberOfFriends(std::string &);

    static bool addFriendRequest (std::string &, std::string &); //parametru:requester, userul prietenului



    //functions for Messages:
    void addChatFile (std::string &, std::string &);

    void addMessageToChatFile(std::string &, std::string &, std::string &);

    std::string convertToChatFile (std::string );

    std::fstream &getChatFile (std::string &, common::openMode);

    std::fstream &getAllChatsFile ();

    void tokenizeString(const std::string &, const char *delimitator, std::vector<std::string> &);

    static void sortVector (std::vector<std::string> &);

    static int getUsernameOrdinal(const std::string&);


    //functions for Settings:
    void changePrivacy(const std::string&, common::privacySetting, pthread_t);


    //functions for user information: privacyType, isAdmin, username
    std::string getUsername (pthread_t ID) const ;

    bool isPrivate(pthread_t ID) const;

    bool isAdmin(pthread_t ID) const;

    Socket getClientSocket(pthread_t) const;

    //functions for posts
    std::vector <common::Post>  getAllPosts (std::string &username, bool isAdmin);

    static std::vector <common::Post>  getAllPostsNotLoggedIn ();

    static void removePost(int );

    static void addPost (const std::string& username, const std::string& text, const std::string& visibleToWhom, const std::string& date);

    bool userInGroupTarget(std::string userWhoPosts, const std::string& userWhoSees, const std::string& friendshipType);


    //alte functii
    void init_mutex();
    void releaseFile(int type); //1->friendFile, 2->ChatFile
    //deconectam de la threadul respectiv clientul
    //returneaza referinta, in caz ca vrem sa folosim intr-o comanda inlantuita
    void disconnect (pthread_t);

    Server &logout (pthread_t); //cand facem logout

    Server & addClientData (const ConnectedClientData &);

    //returnam o copie a structurilor care se exista intr un anumit moment
    //se modifica, constant
    std::list <ConnectedClientData> getClientThreadDataInstant () const;

    void writeToConnectedClientData(std::string,common::privacySetting, pthread_t);

    Server &setup (short, int = Server ::DEFAULT_QUEUE_SIZE);

    void initSocket(short, int);

    void run();

}
;

#endif //QT1_SERVER_H
