#ifndef CLANG_UTILS_LOG_H
#define CLANG_UTILS_LOG_H

#include <string.h>
#include <thread>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../request/request.h"

namespace log
{
    void logServingFile(const std::string &path, const std::string &mimetype)
    {
        std::cout << "Serving file: " << path << " with MIME type: " << mimetype << std::endl;
    }

    void log(const sockaddr_in &server_addr)
    {
        socklen_t client_addr_size = sizeof(struct sockaddr_in);

        char ipstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(server_addr.sin_addr), ipstr, sizeof(ipstr));
        std::cout << "Server IP (" << client_addr_size << "): " << ipstr << std::endl;
    }

    void log(const HttpRequest req)
    {
        for (auto it = req.headers.begin(); it != req.headers.end(); it++)
        {
            std::cout << it->first << " : " << it->second << std::endl;
        }
    }
}

#endif
