#include "server.h"

namespace app
{
    void Server::start()
    {
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0)
        {
            throw new ServerException(new char[]{"Failed to create server socket"});
        }

        socket_in.sin_family = AF_INET;
        socket_in.sin_port = port;
        socket_in.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(socket_fd, (struct sockaddr *)&socket_in, sizeof(socket_in)) < 0)
        {
            throw new ServerException(new char[]{"Failed to bind server socket"});
        }

        if (listen(socket_fd, 5) < 0)
        {
            throw new ServerException(new char[]{"Failed to listen on server socket"});
        };
    };

    void Server::stop()
    {
        close(socket_fd);
    }
}
