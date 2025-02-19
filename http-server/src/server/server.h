#ifndef CLANG_SERVER_H
#define CLANG_SERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <sys/epoll.h>
#include <sys/wait.h>

namespace app
{

    class Server
    {
    private:
        int port, socket_fd;
        sockaddr_in socket_in;

    public:
        Server(int port) : port(port) {};

        void start();

        void stop();

        int &getSocketFd()
        {
            return socket_fd;
        }

        sockaddr_in &getSocketIn()
        {
            return socket_in;
        }

        ~Server() { stop(); };
    };

    class ServerException : public std::exception
    {
    private:
        char *message;

    public:
        ServerException(char *msg) : message(msg) {}

    public:
        char *what()
        {
            return message;
        }
    };

}

#endif
