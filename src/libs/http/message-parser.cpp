#include "../../../include/http.h"

namespace app
{
    HttpMessageParser::HttpMessageParser(std::istream &sock_in) : sock_in(sock_in) {};

    HttpMessage HttpMessageParser::parse()
    {
        std::string request_line;
        if (!std::getline(sock_in, request_line) || request_line.empty())
        {
            throw BadRequestException("HTTP message is empty");
        }

        std::istringstream request_stream(request_line);

        std::string methodStr, path, http_version;
        request_stream >> methodStr >> path >> http_version;

        auto method = stringToHttpMethod(methodStr);
        if (method == HttpMethod::UNKNOWN)
        {
            throw BadRequestException("HTTP method not supported");
        }

        std::map<std::string, std::string> headers;
        size_t contentLength = 0;
        while (std::getline(sock_in, request_line))
        {
            if (request_line == "\r" || request_line == "\r\n")
            {
                break;
            }

            size_t colon = request_line.find(":");
            if (colon != std::string::npos)
            {
                std::string key = request_line.substr(0, colon);
                std::string value = request_line.substr(colon + 2);
                headers[key] = value;

                if (key == "Content-Length")
                {
                    contentLength = std::stoi(value);
                }
            }
        }

        if (!contentLength)
        {
            throw BadRequestException("Content length unkown");
        }

        std::getline(sock_in, request_line);

        return HttpMessage{method, path, http_version, headers, request_line};
    }

    void HttpMessage::toString()
    {
        std::cout
            << "HTTP Message: " << httpMethodToString(method) << "\n";
        std::cout << "Method: " << method << "\n";
        std::cout << "Path: " << path << "\n";
        std::cout << "Version: " << version << "\n";
        for (const auto &entry : headers)
        {
            std::cout << entry.first << ": " << entry.second << "\n";
        }

        std::cout << "Body: " << body << "\n";
    }

}