#ifndef CLANG_UTILS_H
#define CLANG_UTILS_H

#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <locale>
#include <iostream>
#include <sstream>
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

        int str_to_int(std::string_view str);

        void trim(std::string &str);
        void ltrim(std::string &str);
        void rtrim(std::string &str);

        std::string join(std::vector<std::string_view> lines, std::string_view delimiter = "\r\n");
    }
}

#endif
