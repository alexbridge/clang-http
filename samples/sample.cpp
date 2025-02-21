// Adapted from C code example
// at https://www.geeksforgeeks.org/socket-programming-cc/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <stdexcept>
#include <iostream>

#include <algorithm>
#include <cctype>
#include <locale>
#include "../utils/utils.h"

class Socket
{
    int sock;

public:
    // Constructor with socket df
    Socket(int socket) : sock(socket)
    {
        if (sock < 0)
            throw std::runtime_error("Socket creation error");
    }

    // Default constructor creates socket df
    Socket() : Socket(socket(AF_INET, SOCK_STREAM, 0)) {}

    // read string from socket
    std::string rx()
    {
        char buffer[1024] = {0};
        int n = read(sock, buffer, sizeof(buffer));
        std::string str = std::string(buffer, n);
        app::utils::trim(str);
        return str;
    }
    // Output to socket
    void tx(std::string s)
    {
        send(sock, s.c_str(), s.length(), 0);
    }

    int getSocket()
    {
        return sock;
    }
};

class SocketClient : public Socket
{
public:
    // Constructor with socket df
    SocketClient(int socket) : Socket(socket) {}

    // Constructor for IP and port
    SocketClient(std::string address, unsigned short port) : Socket(/* create default socket */)
    {
        struct sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);

        // Convert IPv4 and IPv6 addresses from text to binary form
        int net_address = inet_pton(AF_INET, address.c_str(), &serv_addr.sin_addr);
        if (net_address <= 0)
            throw std::runtime_error("Invalid address: Address not supported");

        int connected = connect(getSocket(), (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if (connected <= 0)
            throw std::runtime_error("Connection Failed");
    }
};

class SocketServer
{
    Socket server; // fd is created in default Socket constructor
    struct sockaddr_in address;
    int opt = 1;

public:
    SocketServer(unsigned short port)
    {
        // Forcefully attaching socket to the port
        int const options = setsockopt(
            server.getSocket(),
            SOL_SOCKET,
            SO_REUSEADDR | SO_REUSEPORT,
            &opt,
            sizeof(opt));
        if (options < 0)
            throw std::runtime_error("setsockopt");

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        // Forcefully attaching socket to the port 8080
        if (bind(
                server.getSocket(),
                (struct sockaddr *)&address,
                sizeof(address)) < 0)
            throw std::runtime_error("bind failed");

        if (listen(server.getSocket(), 3) < 0)
        {
            throw std::runtime_error("listen");
        }
    }
    SocketClient waitForConnection()
    {
        int new_socket;
        int addrlen = sizeof(struct sockaddr_in);
        new_socket = accept(
            server.getSocket(),
            (struct sockaddr *)&address,
            (socklen_t *)&addrlen);
        if (new_socket < 0)
            throw std::runtime_error("accept");
        return SocketClient(new_socket);
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;
    try
    {
        // Normally you'd spawn threads for multiple connections.
        SocketServer srv = SocketServer(8080);

        while (true)
        {
            SocketClient conn = srv.waitForConnection();

            std::string in;
            while (true)
            {
                in = conn.rx();

                std::string lc = std::string(in);
                app::utils::trim(lc);
                std::transform(lc.begin(), lc.end(), lc.begin(), ::tolower);

                if (lc.find("exit") != std::string::npos)
                {
                    conn.tx("Bye\n");
                    close(conn.getSocket());
                    break;
                }

                cout << "[" << in << "]" << endl;

                conn.tx("Server got: " + in + "\n");
            }
        }
    }
    catch (runtime_error &e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    return 0;
}
