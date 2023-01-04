//
// Created by mrnk on 12/4/22.
//

#include "common.h"
#include "errors.h"
#include <string>
#include <stdexcept>

using namespace common;
using namespace errors;

void common:: writeRequest ( Socket socket, ClientRequests request)
{
    //transformam clientrequest in int, scriem acest int
    int requestNumber =  static_cast <int>( request);
    writeRequestNumber(socket, requestNumber);
}

void common:: writeRequestNumber(Socket socket, int requestNumber)
{
    if(write(socket, &requestNumber, sizeof(int)) == -1 )
        //arunc eroare
        throwException(errors::writeRequestNumberError);
}

void common::writeString (Socket socket, const std::string &message)
{
    //trimitem lungimea, urmata de string
    int messageLength = static_cast<int> (message.length());
    if(write(socket, &messageLength, sizeof(int)) == -1)
    {
        printf(errors::writeStringLengthError);
    }

    if(write(socket, message.c_str(), messageLength) == -1 )
    {
        throwException(errors::writeStringStringError);
    }

}
void common::writeResponse (Socket socket, ServerResponse response)
{
    int responseNumber =  static_cast <int>( response);
    common::writeRequestNumber(socket, responseNumber);
}

ClientRequests common::readRequest(Socket socket)
{
    int request;
   if( readBufferInt(socket, request) == 0)
       return common::NO_REQUEST;
    return static_cast<ClientRequests> (request);
}
ServerResponse common:: readResponse (Socket socket)
{
    int response;
    readBufferInt(socket, response);
    return static_cast<ServerResponse> (response);
}
int common::readBufferInt(int fd, int  &pBuf){

    int retVal = read(fd, &pBuf, sizeof(int) );
    return retVal;

}

std::string common:: readString(Socket socket )
{
    int messageLength ;
    common::readBufferInt(socket, messageLength);

    std::string message;
    message.resize(messageLength);

    if (read(socket, message.data(),messageLength) == -1)
    {
        throwException(errors::readStringError);
    }
    message.shrink_to_fit();
    return message;
}

std::vector<std::string> common::tokenizeString(std::string stringToTokenize, const char *delimitator) {
    std::vector<std::string> vectorOfUsernames;

    char *token = strtok(const_cast<char *> (stringToTokenize.c_str()), delimitator);
    while (token != nullptr)
    {
        vectorOfUsernames.emplace_back(token);
        token = strtok(nullptr, delimitator);
    }
    return vectorOfUsernames;

}

std::string common:: vectorToString(std::vector<std::string> vectorOfStrings, const char* delimitator) {
    std::string finalString;
    for (int i = 0; i<vectorOfStrings.size(); i++)
    {
        finalString.append(vectorOfStrings.at(i));
        if(i+1 < vectorOfStrings.size())
            finalString.append(delimitator);
    }
    return finalString;
    //la chatWidget: delimitatorul va fi ", "
    //la conversie in format de allChatsFile : "|"
}
