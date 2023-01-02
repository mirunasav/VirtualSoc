//
// Created by mrnk on 12/30/22.
//

#include "RequestHandler.h"
#include "../common/common.h"
#include "Server.h"
int RequestHandler::handleRequest( ClientThread  & client,  common::ClientRequests request) {
    //map de la enum la functie in loc de request
    //map : ClientRequest - std::function
    //std::unordered_map <int, std::function <void (ClientThread &)> > map;
    //m.emplace(common::requestlogin , &handlelogin)
    //m[request](client);
    switch(request)
    {
        case common::ClientRequests::REQUEST_LOGIN:
            RequestHandler::handleLogin(client);
            return 200;
        case common::ClientRequests::REQUEST_SIGN_UP:
            RequestHandler::handleSignUp(client);
            return 200;
        case common::ClientRequests::REQUEST_LOGOUT:
            RequestHandler::handleLogout(client);
            client.loggedIn = false;
            return 401;
        case common::ClientRequests::REQUEST_ADD_FRIEND:
            RequestHandler::handleAddFriends(client);
            return 200;
        case common::ClientRequests::REQUEST_GET_FRIEND_LIST:
            RequestHandler::handleGetFriendList(client);
            return 200;
        case common::REQUEST_GET_NUMBER_OF_FRIENDS:
            RequestHandler::handleGetNumberOfFriends(client);
            return 200;
        case common::REQUEST_REMOVE_FRIEND:
            RequestHandler::handleRemoveFriend(client);
            return 200;
        case common::REQUEST_CHANGE_TYPE:
            RequestHandler::handleChangeFriendshipType(client);
            return 200;
        case common::REQUEST_GET_PRIVACY_TYPE:
            RequestHandler::handleGetPrivacyType(client);
            return 200;
        case common::REQUEST_GET_CHAT_FILE_READ:
            RequestHandler::handleGetChatFile(client,common::openMode::READ);
            return 200;
        case common::REQUEST_GET_CHAT_FILE_WRITE:
            RequestHandler::handleGetChatFile(client,common::openMode::WRITE);
            return 200;
        case common::REQUEST_GET_ALL_CHATS:
            RequestHandler::handleGetAllChats(client);
            return 200;
        case common::REQUEST_CHANGE_PRIVACY_TYPE_PRIVATE:
            RequestHandler::handleChangePrivacyType(client,common::privacySetting::PRIVATE);
            return 200;
        case common::REQUEST_CHANGE_PRIVACY_TYPE_PUBLIC:
            RequestHandler::handleChangePrivacyType(client,common::privacySetting::PUBLIC);
            return 200;

            //cand se inchide clientul din x / neasteptat, nu din butonul de logout
        case common::NO_REQUEST :
            Server::getInstance().disconnect(client.ID);
            return 499;

    }

}

void RequestHandler::handleLogin(ClientThread &client) {
    //verific daca nu sunt cumva in lista de useri deja conectati
    //verific daca usernameul si parola sunt in fisierul de useri
    std::string username = common::readString(client.clientSocket);
    std::string password = common::readString (client.clientSocket);

    //verificam daca userul nu e deja conectat
    for(const auto & connectedClientData : Server::getInstance().getClientThreadDataInstant())
    {
        if(!connectedClientData.username.empty() && connectedClientData.username==username){
            writeResponse(client.clientSocket,common:: ServerResponse :: LOGIN_USER_ALREADY_CONNECTED);
            return;
        }
    }

    //daca nu e conectat deja, verificam fisierul cu parole
    if(Server::getInstance().checkLogin(username, password, client.ID))
    {
        client.loggedIn = true;
        client.isPrivate = Server::getInstance().isPrivate(client.ID);
        writeResponse(client.clientSocket, common::ServerResponse::LOGIN_SUCCESS);
    }
    else
        writeResponse(client.clientSocket, common::ServerResponse::LOGIN_BAD_USER_PASS);
}

void RequestHandler::handleSignUp(ClientThread &client) {
    std::string username = common::readString(client.clientSocket);
    std::string password = common::readString (client.clientSocket);

    if(Server::getInstance().createUser(username, password,client.ID)) //daca a reusit crearea
    {
        writeResponse(client.clientSocket, common::ServerResponse::CREATE_ACCOUNT_SUCCESS);
        client.loggedIn = true;
        client.isPrivate = Server::getInstance().isPrivate(client.ID);
    }
    else
        writeResponse(client.clientSocket, common::ServerResponse::CREATE_ACCOUNT_USERNAME_EXISTS);
}

void RequestHandler::handleLogout(ClientThread &client) {
    Server::getInstance().logout(client.ID);
    client.loggedIn = false;
}

void RequestHandler::handleAddFriends(ClientThread &client) {
    std::string username = common::readString(client.clientSocket);

    //daca usernameul introdus e chiar al celui care trimite cererea
    for(const auto & connectedClientData : Server::getInstance().getClientThreadDataInstant())
    {
        if(!connectedClientData.username.empty() && connectedClientData.username==username && connectedClientData.threadID == client.ID){
            writeResponse(client.clientSocket,common:: ServerResponse :: ADD_FRIENDS_OWN_USERNAME);
            return;
        }
    }

    if(Server::getInstance().checkUserExists(username)) {
        auto requesterUsername =RequestHandler::getClientUsername(client);

        if( Server::getInstance().addFriend(requesterUsername, username))
            writeResponse(client.clientSocket, common::ServerResponse::ADD_FRIENDS_REQUEST_SENT);
        else
            writeResponse(client.clientSocket, common::ServerResponse::ADD_FRIENDS_ALREADY_FRIEND);

    }
    else
        writeResponse(client.clientSocket, common::ServerResponse::ADD_FRIENDS_INVALID_USER);
}

void RequestHandler::handleGetFriendList(ClientThread &client) {
    auto requesterUsername =RequestHandler::getClientUsername(client);//gasim usernameul celui care cere

    int numberOfFriends = Server::getInstance().getNumberOfFriends(requesterUsername);

    std::fstream & friendsFile = Server::getInstance().getFriendListFile(requesterUsername);
    std::string username, friendshipType;
    for(int i = 1; i<= numberOfFriends; i++){
        friendsFile>>username>>friendshipType;
        common::writeString(client.clientSocket, username);
        common::writeString(client.clientSocket, friendshipType);
    }
    Server::getInstance().releaseFile(common::typesOfFile::friendFile);
}

void RequestHandler::handleGetNumberOfFriends(ClientThread &client) {
    auto requesterUsername =RequestHandler::getClientUsername(client); //gasim usernameul celui care cere
    int numberOfFriends = Server::getInstance().getNumberOfFriends(requesterUsername);
    write(client.clientSocket, &numberOfFriends, sizeof(int));
}

void RequestHandler::handleRemoveFriend(ClientThread &client) {
    auto requesterUsername =RequestHandler::getClientUsername(client);//gasesc ID-ul celui care cere
    auto usernameToRemove = common::readString(client.clientSocket);

    Server::getInstance().removeFriendFromBothLists(requesterUsername, usernameToRemove);
}

void RequestHandler::handleChangeFriendshipType(ClientThread &client) {
    auto requesterUsername =RequestHandler::getClientUsername(client);//gasesc ID-ul celui care cere
    auto friendUsername = common::readString(client.clientSocket);
    auto newFriendshipType = common::readString(client.clientSocket);

    Server::getInstance().changeFriendshipType(requesterUsername, friendUsername,newFriendshipType);
}

void RequestHandler::handleGetPrivacyType(ClientThread &client) {
    if(client.isPrivate) //daca e privat
        writeResponse(client.clientSocket,common::ServerResponse::PRIVACY_TYPE_PRIVATE);
    else
        writeResponse(client.clientSocket,common::ServerResponse::PRIVACY_TYPE_PUBLIC);
}

void RequestHandler::handleChangePrivacyType(ClientThread &client, common::privacySetting privacyType) {
    auto requesterUsername = RequestHandler::getClientUsername(client);
    Server::getInstance().changePrivacy(requesterUsername,privacyType, client.ID);
    client.isPrivate = Server::getInstance().isPrivate(client.ID);
}

void RequestHandler::handleGetAllChats(ClientThread &client) {
    auto requesterUsername =RequestHandler::getClientUsername(client);

    std::fstream & allChatsFile = Server::getInstance().getAllChatsFile();
    std::string usersInChat, chatFilePath;
    std::vector <std::string> usersInChatVector;
    std::list <std::string> chatsWithUser;
    while (allChatsFile >>usersInChat>>chatFilePath) {
        //sirul e user1|
        //parsez sirul
        usersInChatVector = common::tokenizeString(usersInChat, "|");
        for (int i = 0; i< usersInChatVector.size(); i++)
        {
            if(usersInChatVector.at(i) == requesterUsername)
            {
                usersInChatVector.erase(usersInChatVector.begin() + i);
                chatsWithUser.push_back(common::vectorToString(usersInChatVector,","));
                continue;
            }
        }
    }
    Server::getInstance().releaseFile(common::typesOfFile::allChatsFile);

    common::writeRequestNumber(client.clientSocket, chatsWithUser.size());
    for(auto  i : chatsWithUser)
    {
        common::writeString(client.clientSocket, i);
    }
}

void RequestHandler::handleGetChatFile(ClientThread &client, common::openMode mode) {
    auto selectedUsernames = common::readString(client.clientSocket);

    auto requesterUsername =RequestHandler::getClientUsername(client);
    selectedUsernames.append(requesterUsername);
    switch(mode)
    {
        case common::openMode::READ: {
            std::fstream & chatFile = Server::getInstance().getChatFile(selectedUsernames, mode);
            int linesUserSees = 0;
            common::readBufferInt(client.clientSocket, linesUserSees);

            std::string fileLine;
            std::list<std::string> messagesList;
            while (std::getline(chatFile, fileLine)) {
                messagesList.push_back(fileLine);
            }

            int messagesInServerChatFile = messagesList.size();
            int messagesToSendToClient = messagesInServerChatFile - linesUserSees;
            common::writeRequestNumber(client.clientSocket, messagesToSendToClient);

            Server::getInstance().releaseFile(common::typesOfFile::chatFile);

            int index = 0;

            for (auto message: messagesList) {
                if (index < linesUserSees)
                    index++;
                else {
                    common::writeString(client.clientSocket, message);
                }
            }
        }
            break;
        case common::openMode::WRITE:
        {
            auto messageToSend = common::readString(client.clientSocket);
            Server::getInstance().addMessageToChatFile( selectedUsernames, messageToSend, requesterUsername);
        }
            break;
    }

}

void RequestHandler::handleNoRequest(ClientThread &client) {

}

std::string RequestHandler::getClientUsername(ClientThread &client) {
    return Server::getInstance().getUsername(client.ID);
}

