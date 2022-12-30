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
    static void handleLoginRequest (ClientThread & );

};


#endif //QT1_REQUESTHANDLER_H
