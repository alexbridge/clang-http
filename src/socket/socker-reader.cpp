#include "../../include/socket.h"

namespace app
{
    // === SocketStreambuf
    SocketStreambuf::SocketStreambuf(int socket) : sockfd(socket)
    {
        setg(buffer, buffer, buffer);
    };

    int SocketStreambuf::underflow()
    {
        ssize_t bytesRead = recv(
            sockfd,
            buffer,
            SOCKET_READER_BUFFER_SIZE - 1,
            initial_read ? MSG_DONTWAIT : 0);
        if (bytesRead <= 0)
        {
            return EOF;
        }

        initial_read = true;

        buffer[bytesRead] = '\0';

        setg(buffer, buffer, buffer + bytesRead);

        return buffer[0];
    }
}