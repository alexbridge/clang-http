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
        int bytes = read(sockfd, buffer, SOCKET_READER_BUFFER_SIZE);
        if (bytes <= 0)
        {
            return traits_type::eof();
        }

        setg(buffer, buffer, buffer + bytes);

        return traits_type::to_int_type(*gptr());
    }

    void SocketStreambuf::doClose()
    {
        ::close(sockfd);
    }

    // === SocketIstream

    SocketIstream::SocketIstream(int socket) : std::istream(&buf), buf(socket) {}

    void SocketIstream::doClose()
    {
        buf.close();
    }
}