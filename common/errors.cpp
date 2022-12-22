//
// Created by mrnk on 12/22/22.
//

#include <stdexcept>
#include "errors.h"

void errors::throwException(const char * errorMessage) {
    throw std::runtime_error (errorMessage);
}
