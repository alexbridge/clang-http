#include "servlet.h"

namespace servlet
{
    void handleClient(int &socket_fd)
    {
        char client_req_buffer[1024];

        read(socket_fd, client_req_buffer, 1024);

        HttpRequest req = HttpRequest();
        req.parseRequest(client_req_buffer);

        // app::log::log(req);

        HttpResponse res = HttpResponse();
        std::string body = req.path;

        std::string response = res.frameHttpResponse("200", "OK", req.headers, body);

        write(socket_fd, response.c_str(), response.length());
        close(socket_fd);
    }
}
