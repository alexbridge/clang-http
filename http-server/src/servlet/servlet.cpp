#include "servlet.h"

namespace servlet
{
    void handleClient(int &socket_fd)
    {
        char client_req_buffer[1024];

        read(socket_fd, client_req_buffer, 1024);

        HttpRequest req = HttpRequest();
        req.parseRequest(client_req_buffer);

        log::log(req);

        auto mime_type = req.getMimeType(req.path);

        HttpResponse res = HttpResponse();
        std::string body = req.readHtmlFile(req.path);

        std::string response = res.frameHttpResponse("200", "OK", req.headers, body, mime_type);

        log::logServingFile(req.path, mime_type);

        // write to client.
        write(socket_fd, response.c_str(), response.length());
        // close client socket.
        close(socket_fd);
    }
}
