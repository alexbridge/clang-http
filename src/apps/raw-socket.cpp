#include <iostream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <iomanip> // For std::setw

void printRawString(const char *chars, size_t size, std::string prefix)
{

    std::cout << "Print char[] with size: " << size << ": " << prefix << std::endl;

    std::stringstream rawString;
    std::stringstream charsString;
    rawString << "R " + prefix + "\"("; // Start raw string literal

    int i = 0;
    char c;

    while (i < size)
    {
        c = chars[i];

        switch (c)
        {
        case '\0':
            rawString << "\\0";
            break;
        case '\\':
            rawString << "\\\\";
            break; // Escape backslashes
        case '"':
            rawString << "\\\"";
            break; // Escape double quotes
        case '\n':
            rawString << "\\n";
            break; // Escape newlines
        case '\r':
            rawString << "\\r";
            break; // Escape carriage returns
        case '\t':
            rawString << "\\t";
            break; // Escape tabs
        // Add other special characters as needed
        default:
            rawString << c;
            break;
        }

        charsString << static_cast<int>(c) << ", ";

        if (c == '\0')
        {
            // break;
        }

        i++;
    }

    rawString << ")\""; // End raw string literal
    std::cout << "RAW[" << rawString.str() << "]" << std::endl;
    std::cout << "ASCII[" << charsString.str() << "]" << std::endl;
}

class SocketStreambuf : public std::streambuf
{
public:
    SocketStreambuf(int socket) : socket_(socket)
    {
        setg(buffer_, buffer_, buffer_);
    }

protected:
    int underflow() override
    {
        std::cout << " ==== Wait bytes ==== " << __LINE__ << std::endl;
        ssize_t bytesRead = recv(socket_, buffer_, bufferSize - 1, initial_read ? MSG_DONTWAIT : 0);
        std::cout << " ==== Bytes received ==== " << bytesRead << std::endl;
        if (bytesRead > 0)
        {
            if (bytesRead <= bufferSize)
            {
                initial_read = true;
            }

            buffer_[bytesRead] = '\0';
            // printRawString(buffer_, "Buffer");
            //  printLine(buffer_);
            setg(buffer_, buffer_, buffer_ + bytesRead);
            return buffer_[0];
        }
        return EOF;
    }

private:
    static const int bufferSize = 50;
    int socket_;
    char buffer_[bufferSize];
    bool initial_read = false;
};

void playSocket()
{
    // Example socket setup (replace with your actual socket code)
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        std::cerr << "Error creating socket." << std::endl;
        return;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080); // Example port
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Bind failed" << std::endl;
        return;
    }

    listen(sockfd, 1);
    int clientSocket = accept(sockfd, nullptr, nullptr);
    if (clientSocket < 0)
    {
        std::cerr << "Accept failed" << std::endl;
        return;
    }
    // End example socket setup

    SocketStreambuf socketBuf(clientSocket);
    std::istream socketStream(&socketBuf);

    std::string line;

    int contentLength;

    while (std::getline(socketStream, line))
    {
        size_t colon = line.find(":");
        if (colon != std::string::npos)
        {
            std::string key = line.substr(0, colon);
            std::string value = line.substr(colon + 2);
            if (key == "Content-Length")
            {
                contentLength = std::stoi(value);
            }
        }

        printRawString(line.c_str(), line.length() + 1, "Line: " + line);

        if (line == "\r" || line == "\r\n")
        {
            // Header separator
            break;
        }
    }

    std::cout << __LINE__ << "Content length: " << contentLength << typeid(contentLength).name() << std::endl;

    getline(socketStream, line);
    std::cout << __LINE__ << ": " << line << std::endl;

    std::string response = "HTTP/1.1 200 OK \r\n"
                           "Content-Type: text/plain \r\n"
                           "Connection: close \r\n";

    send(clientSocket, response.c_str(), response.length(), 0);

    close(clientSocket);
    close(sockfd);
}

int main()
{
    playSocket();

    return 0;
}