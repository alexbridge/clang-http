#include "../../include/socket.h"

namespace app
{
    SocketClient::SocketClient(int socket) : Socket(socket) {}

    SocketClient::SocketClient(std::string address, unsigned short port) : Socket()
    {
        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);

        // Convert IPv4 and IPv6 addresses from text to binary form
        int net_address = inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr);
        if (net_address <= 0)
            throw std::runtime_error("Invalid address: Address not supported");

        int connected = connect(getSocket(), (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if (connected <= 0)
            throw std::runtime_error("Connection Failed");
    }
}