#include "../../../include/http.h"

namespace app
{
    HttpMessageParser::HttpMessageParser(std::istream &sock_in) : sock_in(sock_in) {};

    void HttpMessageParser::parse()
    {
        std::string request_line;
        if (!std::getline(sock_in, request_line) || request_line.empty())
        {
            std::cerr << "Invalid request line\n";
            return;
        }

        std::istringstream request_stream(request_line);
        std::string method, path, http_version;
        request_stream >> method >> path >> http_version;

        std::cout << "Method: " << method << "\n";
        std::cout << "Path: " << path << "\n";
        std::cout << "HTTP Version: " << http_version << "\n";

        // Read headers
        std::map<std::string, std::string> headers;
        std::string header_line;
        while (std::getline(sock_in, header_line) && header_line != "\r")
        {
            size_t colon = header_line.find(":");
            if (colon != std::string::npos)
            {
                std::string key = header_line.substr(0, colon);
                std::string value = header_line.substr(colon + 2); // Skip ": "
                headers[key] = value;
                std::cout << key << ": " << value << "\n";
            }
        }
        std::cout << "\n--- End of HTTP Request ---\n";
    }
}