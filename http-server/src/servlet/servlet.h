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
#include "../utils/utils.h"
#include "../http/message-parser.h"

namespace servlet
{
    void handleClient(int &socket_fd);
}

#endif
