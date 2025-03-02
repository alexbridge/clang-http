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

        char buffer[contentLength];

        sock_in.read(buffer, contentLength);

        std::cout << "Last: " << contentLength << ": " << buffer << std::endl;

        std::cout << "\n--- End of HTTP Request ---\n";

        return HttpMessage{method, path, http_version, headers, std::string(buffer)};
    }

    HttpMethod HttpMessageParser::stringToHttpMethod(const std::string &str)
    {
        static const std::map<std::string, HttpMethod> map = {
            {"GET", HttpMethod::GET},
            {"POST", HttpMethod::POST},
            {"PUT", HttpMethod::PUT},
            {"PATCH", HttpMethod::PATCH},
            {"HEAD", HttpMethod::HEAD},
            {"DELETE", HttpMethod::DELETE},
            {"OPTIONS", HttpMethod::OPTIONS}};

        auto it = map.find(str);
        if (it != map.end())
        {
            return it->second;
        }
        else
        {
            return HttpMethod::UNKNOWN;
        }
    }
}