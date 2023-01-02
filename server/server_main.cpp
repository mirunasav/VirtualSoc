//
// Created by mrnk on 12/4/22.
//

#include "Server.h"
#include "../common/common.h"
#include <CDS/util/JSON>

using namespace common;
using namespace cds::json;
int main () {

    Server::getInstance().setup(SERVER_PORT).run();
}