#include "../../include/socket.h"

namespace app
{
    SocketClient::SocketClient(SocketAddressIn &addressIn) : Socket(), SocketAddress(addressIn)
    {
        std::cout << "SocketClient::constructor(string ip, short port)\n";
    }

    void SocketClient::connect()
    {
        int connected = ::connect(sockFd, (struct sockaddr *)&address, sizeof(address));
        if (connected <= 0)
        {
            throw std::runtime_error("Socket client: connection failed");
        }
    }
}
