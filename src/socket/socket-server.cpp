#include "../../include/socket.h"

namespace app
{
    SocketServer::SocketServer(SocketAddressIn &addressIn) : Socket(), SocketAddress(addressIn)
    {
        // Forcefully attaching socket to the port
        int options = setsockopt(
            sockFd,
            SOL_SOCKET,
            SO_REUSEADDR | SO_REUSEPORT,
            &socketOptions,
            sizeof(socketOptions));
        if (options < 0)
        {
            throw std::runtime_error("set socket options");
        }

        // Forcefully attaching socket to the port
        if (bind(sockFd, (struct sockaddr *)&address, sizeof(address)) < 0)
        {
            throw std::runtime_error("Bind to socket address failed");
        }

        if (listen(sockFd, 3) < 0)
        {
            throw std::runtime_error("Listen error");
        }
    }

    std::unique_ptr<Socket> SocketServer::waitForConnection()
    {
        int addrlen = sizeof(address);
        int new_socket = accept(
            sockFd,
            (struct sockaddr *)&address,
            (socklen_t *)&addrlen);
        if (new_socket < 0)
        {
            std::cerr << "Socket Accept failed" << new_socket << "\n";
            throw std::runtime_error("Socket not accepted");
        }
        return std::make_unique<Socket>(new_socket);
    }
}
