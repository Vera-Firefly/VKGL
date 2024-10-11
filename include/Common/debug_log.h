#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

#include <iostream>
#include <cstdlib>

#define OUT_DBG(message) \
    std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " << message << std::endl

#endif