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

            std::vector<std::string_view> response{
                app::http::header::HTTP_OK,
                app::http::header::CONTENT_TYPE + ": text/plain",
                app::http::header::CONNECTION + ": close"};

            sock->writeToSocket(app::utils::join(response));
        }
        catch (const HttpClientError &e)
        {
            std::cerr << typeid(e).name() << ": " << e.what() << '\n';

            std::vector<std::string_view> response{
                app::http::header::HTTP_BAD_REQUEST,
                app::http::header::CONTENT_TYPE + ": text/plain",
                app::http::header::CONNECTION + ": close"};

            sock->writeToSocket(app::utils::join(response));
        }
    }
}