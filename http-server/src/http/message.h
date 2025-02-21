#ifndef CLANG_HTTP_MESSAGE_H
#define CLANG_HTTP_MESSAGE_H

#include <string>
#include <map>
#include "header.h"

namespace http
{
    enum method
    {
        GET,
        POST,
        PUT,
        PATCH,
        HEAD,
        DELETE
    };

    namespace message
    {
        struct HttpMessage
        {
            http::method method;
            std::string path;
            std::map<std::string, std::string> headers;
            std::string body;
        };
    }
}

#endif