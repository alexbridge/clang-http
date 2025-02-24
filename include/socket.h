#ifndef CLANG_SOCKET_H
#define CLANG_SOCKET_H

// Adapted from C code example
// at https://www.geeksforgeeks.org/socket-programming-cc/
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

namespace app
{
    class Socket
    {
    private:
        int sock;

    public:
        explicit Socket(int socket);

        explicit Socket();

        std::string readFromSocket();

        void writeToSocket(std::string s);

        int getSocket();
    };

    class SocketClient : public Socket
    {
    public:
        explicit SocketClient(int socket);
        explicit SocketClient(std::string address, unsigned short port);
    };

    class SocketServer
    {
        Socket server;
        struct sockaddr_in address;
        int opt = 1;

    public:
        explicit SocketServer(unsigned short port);

        SocketClient waitForConnection();
    };
}

#endif