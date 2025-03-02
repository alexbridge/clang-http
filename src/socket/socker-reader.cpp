#include "../../include/socket.h"

namespace app
{
    // === SocketStreambuf
    SocketStreambuf::SocketStreambuf(int socket) : sockfd(socket)
    {
        // Set buffer pointers
        setg(buffer, buffer, buffer);
    };

    int SocketStreambuf::underflow()
    {
        ssize_t bytesRead = recv(sockfd, buffer, SOCKET_READER_BUFFER_SIZE, 0);
        if (bytesRead <= 0)
        {
            return EOF; // Error or end of stream
        }
        setg(buffer, buffer, buffer + bytesRead);

        return buffer[0];
    }
}