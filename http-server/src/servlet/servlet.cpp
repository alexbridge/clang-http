#include <unistd.h>
#include "../request/request.cpp"
#include "../response/response.cpp"
#include "../utils/log-utils.cpp"

namespace servlet
{
    void handleClient(int client_socket_fd)
    {
        char client_req_buffer[1024];
        // handle client request.
        // read from the client.
        read(client_socket_fd, client_req_buffer, 1024);
        HttpRequest req = HttpRequest();

        req.parseRequest(client_req_buffer);
        // for(auto it = req.headers.begin(); it != req.headers.end(); it++){
        //     std::cout << it->first << " : " << it->second << std::endl;
        // }
        std::string mimetype = req.getMimeType(req.path);
        // std::cout << "Mimetype: " << mimetype << std::endl;

        HttpResponse res = HttpResponse();
        std::string body = req.readHtmlFile(req.path);
        std::string response = res.frameHttpResponse("200", "OK", req.headers, body, mimetype);

        log::logServingFile(req.path, mimetype);

        // write to client.
        write(client_socket_fd, response.c_str(), response.length());
        // close client socket.
        close(client_socket_fd);
    }
}
