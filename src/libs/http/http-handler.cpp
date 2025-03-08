#include "../../../include/http.h"

namespace app
{
    void HttpHandler::handle(std::unique_ptr<Socket> sock)
    {
        if (sock->closed)
        {
            std::cerr << "HttpHandler: socket closed\n";
            return;
        }

        std::cout << "\n--- Start of HTTP Message ---\n";

        // app::SocketIstream sock_in(sock->sockFd);
        app::SocketStreambuf sock_in(sock->sockFd);

        std::istream socketStream(&sock_in);

        app::HttpMessageParser http_parser(socketStream);

        try
        {
            auto message = http_parser.parse();

            message.toString();

            std::cout << "\n--- End of HTTP Message ---\n";

            std::string response = "HTTP/1.1 200 OK \r\n"
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