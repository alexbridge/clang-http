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

#define METHOD_ENUM(X) \
    X(GET)             \
    X(POST)            \
    X(PUT)             \
    X(PATCH)           \
    X(HEAD)            \
    X(DELETE)          \
    X(OPTIONS)         \
    X(UNKNOWN)

namespace app
{
    enum HttpMethod
    {
#define GENERATE_ENUM_VALUE(value) value,
        METHOD_ENUM(GENERATE_ENUM_VALUE)
#undef GENERATE_ENUM_VALUE
    };

    static const std::map<HttpMethod, std::string> httpMethodToStrMap = {
#define GENERATE_ENUM_NAME(value) {HttpMethod::value, #value},
        METHOD_ENUM(GENERATE_ENUM_NAME)
#undef GENERATE_ENUM_NAME
    };

    static const std::map<std::string, HttpMethod> httpStrToMethodMap = {
#define GENERATE_ENUM_NAME(value) {#value, HttpMethod::value},
        METHOD_ENUM(GENERATE_ENUM_NAME)
#undef GENERATE_ENUM_NAME
    };

    std::string httpMethodToString(HttpMethod method);

    HttpMethod stringToHttpMethod(const std::string &str);

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