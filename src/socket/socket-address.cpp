#include "../../include/socket.h"

namespace app
{
    SocketAddress::SocketAddress(SocketAddressIn &addressIn) : address{}
    {
        std::cout << "SocketAddress::constructor(string ip, short port)" << addressIn.ip << ":" << addressIn.port << "\n";

        address.sin_family = AF_INET;
        address.sin_port = htons(addressIn.port);
        int net_address = inet_pton(AF_INET, addressIn.ip.c_str(), &address.sin_addr);
        if (net_address <= 0)
        {
            throw std::runtime_error("Invalid ip: address not supported");
        }
    }
}