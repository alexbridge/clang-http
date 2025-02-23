#ifndef CLANG_REQUEST_H
#define CLANG_REQUEST_H

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../http/message.h"

namespace http
{
    namespace request
    {

        struct HttpRequest
        {

            http::method method;
            std::string path;
            std::map<std::string, std::string> headers;
            std::string body;
        };
    }
}

#endif