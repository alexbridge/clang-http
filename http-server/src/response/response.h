#ifndef CLANG_RESPONSE_H
#define CLANG_RESPONSE_H

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

class HttpResponse
{
    std::string status_code;
    std::string status_message;
    std::map<std::string, std::string> headers;
    std::string body;

public:
    std::string frameHttpResponse(
        std::string status_code,
        std::string status_message,
        std::map<std::string, std::string> headers,
        std::string body);
};

#endif