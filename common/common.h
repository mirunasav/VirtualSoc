//
// Created by mrnk on 12/4/22.
//

#ifndef QT1_COMMON_H
#define QT1_COMMON_H

#include <string>
#include <cstring>
#include <unistd.h>
#include <utility>
#include <vector>

#define BUFFER_LENGTH 256
typedef int Socket;
constexpr int SOCKET_ERROR = -1;

namespace common {

    enum ClientRequests : int
    {
        //cand vrem sa facem login
        REQUEST_LOGIN = 300,

        REQUEST_SIGN_UP  = 305,

        REQUEST_LOAD_FEED = 310,

        REQUEST_LOAD_FEED_NOT_LOGGED_IN = 315,

        REQUEST_REMOVE_POST= 320,

        REQUEST_NEW_POST = 330,

        REQUEST_SEND_FRIEND_REQUEST = 331,

        REQUEST_ACCEPT_REQUEST = 332,

        REQUEST_DENY_REQUEST = 333,

        REQUEST_ADD_FRIEND = 335,

        REQUEST_GET_FRIEND_LIST = 340,

        REQUEST_GET_REQUESTS_LIST = 345,

        REQUEST_GET_BLOCKED_LIST = 346,

        REQUEST_BLOCK_USER= 347,

        REQUEST_UNBLOCK_USER= 348,

        REQUEST_GET_NUMBER_OF_FRIENDS = 350,

        REQUEST_REMOVE_FRIEND = 360,

        REQUEST_CHANGE_TYPE = 365,

        REQUEST_GET_PRIVACY_TYPE = 370,

        REQUEST_CHANGE_PRIVACY_TYPE_PRIVATE = 375,

        REQUEST_CHANGE_PRIVACY_TYPE_PUBLIC = 376,

        REQUEST_GET_CHAT_FILE_READ = 380,

        REQUEST_GET_CHAT_FILE_WRITE= 385,

        REQUEST_GET_ALL_CHATS = 390,

        REQUEST_LOGOUT = 490,

        NO_REQUEST = 400

    };

    enum ServerResponse : int{
        LOGIN_SUCCESS = 200,

        LOGIN_ADMIN_SUCCESS = 300,

        LOGIN_BAD_USER_PASS = 400,

        LOGIN_USER_ALREADY_CONNECTED = 401,

        CREATE_ACCOUNT_USERNAME_EXISTS = 402,

        CREATE_ACCOUNT_SUCCESS = 403,

        ADD_FRIENDS_REQUEST_SENT = 405,

        ADD_FRIENDS_ADDED = 411,

        ADD_FRIENDS_INVALID_USER = 406,

        ADD_FRIENDS_ALREADY_FRIEND = 407,

        ADD_FRIENDS_OWN_USERNAME = 408,

        ADD_FRIENDS_REQUEST_ALREADY_SENT= 409,

        ADD_FRIENDS_USER_BLOCKED= 413,

        ADD_FRIENDS_USER_BLOCKED_YOU= 414,

        PRIVACY_TYPE_PUBLIC = 410,

        PRIVACY_TYPE_PRIVATE = 411,

    };

    enum typesOfFile : int
    {
        friendFile = 1,
        chatFile = 2,
        allChatsFile = 3,
        allPostsJson = 4,
        requestsFile = 5,
        blockedUsersFile = 6
    };

    enum typesOfFriend : int
    {
        NORMAL_FRIEND = 1,
        CLOSE_FRIEND = 2,
        Acquaintance = 3
    };
    enum privacySetting : int
    {
        PUBLIC = 0, //!isPrivate
        PRIVATE = 1, //isPrivate
        ADMIN = 2
    };

    enum openMode : int
    {
        READ = 0,
        WRITE = 1
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

    int readBufferInt(int fd, int & pBuf);

    void writeRequestNumber(Socket socket, int requestNumber);
    void writeRequest ( Socket socket, ClientRequests request);
    void writeString (Socket socket, const std::string &message);
    void writeResponse (Socket , ServerResponse );

    std::vector<std::string> tokenizeString(std::string, const char * );
    std::string vectorToString (  std::vector<std::string>, const char *);

    class Post
    {
    private:
        std::string userWhoPosts;
        std::string textOfPost;
        std::string visibleToWhom;
        std::string dateOfPost;
        int ID;
    public:
        Post(std::string  userWhoPosts,std::string  textOfPost,std::string  visibleToWhom,std::string  dateOfPost, int ID)
        : userWhoPosts(std::move(userWhoPosts)), textOfPost(std::move(textOfPost)), visibleToWhom(std::move(visibleToWhom)), dateOfPost(std::move(dateOfPost)), ID(ID)
        {}
        const std::string & getUserWhoPosts()
        {
            return this->userWhoPosts;
        };
        const std::string & getTextOfPost()
        {
            return this->textOfPost;
        };
        const std::string & getVisibleToWhom()
        {
            return this->visibleToWhom;
        };
        const std::string & getDateOfPost()
        {
            return this->dateOfPost;
        };
        const int & getID()
        {
            return this->ID;
        }
    };
    };


#endif //QT1_COMMON_H
