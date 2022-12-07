//
// Created by mrnk on 12/4/22.
//

#include "Server.h"
#include "../common/common.h"
using namespace common;
int main () {
    Server::getInstance().setup(SERVER_PORT).run();
}