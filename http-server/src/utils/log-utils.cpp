#include <string.h>
#include <thread>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace log
{
    // utility function to log the serving of a file.
    void logServingFile(const std::string &path, const std::string &mimetype)
    {
        std::cout << "Serving file: " << path << " with MIME type: " << mimetype << std::endl;
    }

    void logServerAddr(const sockaddr_in &server_addr)
    {
        socklen_t client_addr_size = sizeof(struct sockaddr_in);

        char ipstr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(server_addr.sin_addr), ipstr, sizeof(ipstr));
        std::cout << "Server IP (" << client_addr_size << "): " << ipstr << std::endl;
    }
}
