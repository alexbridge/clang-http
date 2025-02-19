#include <string>
#include <thread>
#include <sys/socket.h>
#include "servlet/servlet.cpp"
#include "server/server.cpp"
#include "utils/number-utils.h"

int main(int argc, char *argv[])
{
    std::cout << "Number of arguments: " << argc << std::endl;

    if (argc <= 1)
    {
        std::cerr << "Provide a server port";
        return 1;
    }

    for (int i = 0; i < argc; ++i)
    {
        std::cout << "Argument " << i << " : " << argv[i] << std::endl;
    }

    int port = app::str_to_int(argv[1]);

    app::Server server = app::Server(port);

    server.start();

    int socket_fd = server.getSocketFd();
    sockaddr_in socket_in = server.getSocketIn();

    socklen_t client_addr_size = sizeof(struct sockaddr_in);

    while (1)
    {
        int client_socket_fd = accept(socket_fd, (struct sockaddr *)&socket_in, &client_addr_size);
        if (client_socket_fd < 0)
        {
            std::cerr << "Failed to accept client request." << std::endl;
            exit(1);
        }

        std::thread clientThread(servlet::handleClient, client_socket_fd);
        clientThread.detach();
    }

    return 0;
}