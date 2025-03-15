#include "../../include/socket.h"

namespace app
{
    Socket::Socket(int socket) : sockFd(socket)
    {
        std::cout << "Socket::constructor(int socket): " << sockFd << std::endl;
    }

    Socket::Socket() : Socket(socket(AF_INET, SOCK_STREAM, 0))
    {
        std::cout << "Socket::default constructor()" << sockFd << std::endl;
    }

    std::string Socket::readFromSocket()
    {
        char buffer[1024] = {0};

        int n = read(sockFd, buffer, sizeof(buffer));
        if (n <= 0)
        {
            return "";
        }

        std::string str = std::string(buffer, n);
        app::utils::trim(str);
        return str;
    }

    void Socket::writeToSocket(const std::string &s)
    {
        send(sockFd, s.c_str(), s.length(), 0);
    }

    Socket::~Socket()
    {
        std::cout << "Socket::destructor: " << sockFd << std::endl;
        doClose();
    }

    void Socket::doClose()
    {
        if (!closed)
        {
            std::cout << "Socket::close: " << sockFd << std::endl;
            ::close(sockFd);
        }
    }
}
