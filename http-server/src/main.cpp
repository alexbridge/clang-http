#include <string>
#include <atomic>
#include <thread>
#include <chrono>
#include <sys/socket.h>
#include "servlet/servlet.h"
#include "server/server.h"
#include "utils/utils.h"

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

    int port = app::utils::str_to_int(argv[1]);

    app::Server server = app::Server(port);

    server.start();

    int socket_fd = server.getSocketFd();

    std::cout << "Socket FD: " << socket_fd << std::endl;

    sockaddr_in socket_in = server.getSocketIn();

    socklen_t client_addr_size = sizeof(struct sockaddr_in);

    std::atomic_int requests{0};

    while (1)
    {
        requests++;
        int client_socket_fd = accept(socket_fd, (struct sockaddr *)&socket_in, &client_addr_size);

        std::cout << "[" << requests << "]: memory used: " << app::log::usedRem() << "\r" << std::flush;

        if (client_socket_fd < 0)
        {
            std::cerr << "Failed to accept client request." << std::endl;
            exit(1);
        }

        std::thread(servlet::handleClient, std::ref(client_socket_fd)).detach();
    }

    return 0;
}