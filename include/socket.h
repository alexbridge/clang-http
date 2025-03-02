#ifndef CLANG_SOCKET_H
#define CLANG_SOCKET_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <locale>
#include "utils.h"
#include "common.h"

namespace app
{
    class Socket : public app::Closable
    {
    protected:
        void doClose() override;

    public:
        int sockFd = 0;

        explicit Socket();

        explicit Socket(int socket);

        std::string readFromSocket();

        void writeToSocket(std::string str);

        ~Socket();
    };

    struct SocketAddressIn
    {
        std::string ip;
        unsigned short port;
    };

    class SocketAddress
    {
    public:
        struct sockaddr_in address;

        explicit SocketAddress(SocketAddressIn &addressIn);
    };

    class SocketClient : public Socket, public SocketAddress
    {
    public:
        explicit SocketClient(SocketAddressIn &addressIn);

        void connect();
    };

    class SocketServer : public Socket, public SocketAddress
    {
    private:
        int socketOptions;

    public:
        explicit SocketServer(SocketAddressIn &addressIn);

        std::unique_ptr<Socket> waitForConnection();
    };

#define SOCKET_READER_BUFFER_SIZE 1024

    class SocketStreambuf : public std::streambuf
    {
    private:
        int sockfd;
        char buffer[SOCKET_READER_BUFFER_SIZE];

    protected:
        int underflow() override;

    public:
        explicit SocketStreambuf(int socket);
    };
}

#endif