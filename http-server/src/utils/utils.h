#ifndef CLANG_UTILS_LOG_H
#define CLANG_UTILS_LOG_H

#include <string.h>
#include <thread>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../request/request.h"

namespace app
{
    namespace log
    {
        void log(const sockaddr_in &server_addr);

        void log(const HttpRequest req);
    }

    namespace utils
    {
        int str_to_int(std::string &str);

        int str_to_int(char *str);
    }
}

#endif
