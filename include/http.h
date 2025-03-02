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
#include "socket.h"

namespace app
{
    enum HttpMethod
    {
        GET,
        POST,
        PUT,
        PATCH,
        HEAD,
        DELETE,
        OPTIONS,
        UNKNOWN
    };

    struct HttpMessage
    {
        HttpMethod method;
        std::string path;
        std::string version;
        std::map<std::string, std::string> headers;
        std::string body;

        void toString();
    };

    class HttpHandler
    {
    public:
        static void handle(std::unique_ptr<Socket> sock);

        HttpHandler() = default;
        HttpHandler(HttpHandler const &) = delete;
        HttpHandler &operator=(HttpHandler const &) = delete;
    };

    class HttpMessageParser
    {
    private:
        std::istream &sock_in;

    public:
        explicit HttpMessageParser(std::istream &sock_in);

        HttpMessage parse();

        HttpMethod stringToHttpMethod(const std::string &str);
        HttpMessageParser() = delete;
        HttpMessageParser(HttpMessageParser const &) = delete;
        HttpMessageParser &operator=(HttpMessageParser const &) = delete;
    };

    class HttpClientError : public std::runtime_error
    {
    public:
        HttpClientError(const std::string &message) : std::runtime_error(message) {}
    };

    class BadRequestException : public HttpClientError
    {
    public:
        BadRequestException(const std::string &message) : HttpClientError(message) {}
    };

}

#endif