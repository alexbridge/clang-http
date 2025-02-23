#ifndef CLANG_RESPONSE_H
#define CLANG_RESPONSE_H

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

namespace http
{

    namespace response
    {
        struct HttpResponse
        {
            std::string status_code;
            std::string status_message;
            std::map<std::string, std::string> headers;
            std::string body;
        };
    }
}

#endif