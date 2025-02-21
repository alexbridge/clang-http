#include "message.h"

namespace http
{
    namespace message
    {
        HttpMessage::HttpMessage(
            http::method method,
            std::string path,
            std::map<std::string, std::string> headers,
            std::string body) : method(method), path(path), headers(headers), body(body) {}

        http::method HttpMessage::getMethod()
        {
            return http::method();
        }

        std::string HttpMessage::getPath()
        {
            return std::string();
        }

        std::map<std::string, std::string> HttpMessage::getHeaders()
        {
            return std::map<std::string, std::string>();
        }

        std::string HttpMessage::getBody()
        {
            return std::string();
        };
    };
}