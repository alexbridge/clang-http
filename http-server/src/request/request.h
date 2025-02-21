#ifndef CLANG_REQUEST_H
#define CLANG_REQUEST_H

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

/*
        void log(const sockaddr_in &server_addr)
        {
            socklen_t client_addr_size = sizeof(struct sockaddr_in);

            char ipstr[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(server_addr.sin_addr), ipstr, sizeof(ipstr));
            std::cout << "Server:" << ipstr << "(" << client_addr_size << "): " << ntohs(server_addr.sin_port) << std::endl;
        }

        void log(const HttpRequest req)
        {
            for (auto it = req.headers.begin(); it != req.headers.end(); it++)
            {
                std::cout << it->first << " : " << it->second << std::endl;
            }
        }


*/

class HttpRequest
{

public:
      std::string method;
      std::string path;
      std::map<std::string, std::string> headers;

      void parseRequest(const std::string &raw_request);
};

#endif