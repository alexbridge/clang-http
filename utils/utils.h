#ifndef CLANG_UTILS_LOG_H
#define CLANG_UTILS_LOG_H

#include <string>
#include <algorithm>
#include <thread>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "sys/types.h"
#include "sys/sysinfo.h"

namespace app
{

    namespace utils
    {
        long long usedRem();
        int str_to_int(std::string &str);

        int str_to_int(char *str);

        void trim(std::string &str);
        void ltrim(std::string &str);
        void rtrim(std::string &str);
    }
}

#endif
