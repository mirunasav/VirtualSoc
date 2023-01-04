//
// Created by mrnk on 12/30/22.
//

#ifndef QT1_REQUESTHANDLER_H
#define QT1_REQUESTHANDLER_H

#include "../common/common.h"
#include "ClientThread.h"
class RequestHandler {
public:
    RequestHandler() = default;
    static int handleRequest (ClientThread & , common::ClientRequests);
    static void handleLogin (ClientThread & );
    static void handleSignUp (ClientThread & );
    static void handleAddFriends (ClientThread & );
    static void handleGetNumberOfFriends (ClientThread & );
    static void handleGetFriendList (ClientThread & );
    static void handleRemoveFriend (ClientThread & );
    static void handleChangeFriendshipType (ClientThread & );
    static void handleGetPrivacyType (ClientThread & );
    static void handleChangePrivacyType (ClientThread & , common::privacySetting); //private si public
    static void handleGetChatFile (ClientThread & , common::openMode);//read si write
    static void handleGetAllChats (ClientThread & );
    static void handleLogout (ClientThread & );
    static void handleAddNewPost (ClientThread & );
    static void handleLoadFeed (ClientThread & );
    static void handleLoadFeedNotLoggedIn (ClientThread & );
    static void handleRemovePost (ClientThread & );
    static void handleNoRequest (ClientThread & ); //cand se inchide random clientul, nu din logout
    static std::string getClientUsername (ClientThread &);


};


#endif //QT1_REQUESTHANDLER_H
