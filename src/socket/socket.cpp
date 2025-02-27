#include "../../include/socket.h"

namespace app
{
    Socket::Socket(int socket) : sock(socket) {}

    Socket::Socket() : Socket(socket(AF_INET, SOCK_STREAM, 0)) {}

    std::string Socket::readFromSocket()
    {
        char buffer[1024] = {0};

        int n = read(sock, buffer, sizeof(buffer));
        if (n <= 0)
        {
            return "";
        }

        std::string str = std::string(buffer, n);
        app::utils::trim(str);
        return str;
    }

    void Socket::writeToSocket(std::string s)
    {
        send(sock, s.c_str(), s.length(), 0);
    }

    int Socket::getSocket()
    {
        return sock;
    }
}

void app::Socket::doClose()
{
    ::close(sock);
}
