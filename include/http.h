#ifndef CLANG_HTTP_H
#define CLANG_HTTP_H

#include <iostream>
#include <streambuf>
#include <istream>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <map>

namespace app
{
    class HttpMessageParser
    {
    private:
        std::istream &sock_in;

    public:
        explicit HttpMessageParser(std::istream &sock_in);

        void parse();

        HttpMessageParser() = delete;
        ~HttpMessageParser() = default;
        HttpMessageParser(HttpMessageParser const &) = delete;
        HttpMessageParser &operator=(HttpMessageParser const &) = delete;
    };

}

#endif