#include "../../../include/http.h"

namespace app
{
    void HttpMessage::toString()
    {
        std::cout
            << "HTTP Message: " << this << "\n";
        std::cout << "Method: " << method << "\n";
        std::cout << "Path: " << path << "\n";
        std::cout << "Version: " << version << "\n";
        std::cout << "Body: " << body << "\n";

        for (const auto &entry : headers)
        {
            std::cout << entry.first << ": " << entry.second << "\n";
        }
    }

    void HttpHandler::handle(std::unique_ptr<Socket> sock)
    {
        if (sock->closed)
        {
            std::cerr << "HttpHandler: socket closed\n";
            return;
        }

        // app::SocketIstream sock_in(sock->sockFd);
        app::SocketStreambuf sock_in(sock->sockFd);

        std::istream socketStream(&sock_in);

        app::HttpMessageParser http_parser(socketStream);

        try
        {
            auto message = http_parser.parse();

            message.toString();

            std::string response = "HTTP/1.1 200 \r\n"
                                   "Content-Type: text/plain \r\n"
                                   "Connection: close \r\n";

            sock->writeToSocket(response);
        }
        catch (const HttpClientError &e)
        {
            std::cerr << typeid(e).name() << ": " << e.what() << '\n';

            std::string response = R"(
                HTTP/1.1 400 Bad Request
                Content-Type: text/plain
                )";
            sock->writeToSocket(response);
        }
    }
}