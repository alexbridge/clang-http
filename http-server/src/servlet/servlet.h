#ifndef CLANG_SERVLET_H
#define CLANG_SERVLET_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <sys/epoll.h>
#include <sys/wait.h>
#include "../request/request.h"
#include "../response/response.h"
#include "../server/server.h"
#include "../utils/log-utils.h"

namespace servlet
{
    void handleClient(int &socket_fd);
}

#endif
