#include "../../include/socket.h"

namespace app
{
    SocketServer::SocketServer(unsigned short port)
    {
        // Forcefully attaching socket to the port
        int const options = setsockopt(
            server.getSocket(),
            SOL_SOCKET,
            SO_REUSEADDR | SO_REUSEPORT,
            &opt,
            sizeof(opt));
        if (options < 0)
            throw std::runtime_error("setsockopt");

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        // Forcefully attaching socket to the port 8080
        if (bind(
                server.getSocket(),
                (struct sockaddr *)&address,
                sizeof(address)) < 0)
            throw std::runtime_error("Bind failed");

        if (listen(server.getSocket(), 3) < 0)
        {
            throw std::runtime_error("Listen error");
        }
    }
    SocketClient SocketServer::waitForConnection()
    {
        int new_socket;
        int addrlen = sizeof(struct sockaddr_in);
        new_socket = accept(
            server.getSocket(),
            (struct sockaddr *)&address,
            (socklen_t *)&addrlen);
        if (new_socket < 0)
        {
            std::cerr << "Socket Accept failed\n";
            throw std::runtime_error("Socket not accepted");
        }
        return SocketClient(new_socket);
    }
}

void app::SocketServer::close()
{
    server.close();
}
