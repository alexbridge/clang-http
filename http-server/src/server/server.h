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

class Server
{
    int port;

public:
    Server(char *charPort);

    int start(sockaddr_in &server_address);

    void stop();
};

#endif
