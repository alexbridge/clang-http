#include "server.h"

Server::Server(char *charPort)
{
    try
    {
        port = std::stoi(charPort);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
};

int Server::start(sockaddr_in &server_address)
{
    int server_socket_fd;
    server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_fd < 0)
    {
        std::cerr << "Failed to create server socket." << std::endl;
        exit(1);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        std::cerr << "Failed to bind server socket." << std::endl;
        exit(1);
    }

    if (listen(server_socket_fd, 5) < 0)
    {
        std::cerr << "Failed to listen on server socket." << std::endl;
        exit(1);
    }

    std::cout << "Server started on port : " << port << std::endl;

    return server_socket_fd;
};

void Server::stop() {
    // TODO
    // close the server socket.
};