#include <atomic>
#include "../../include/socket.h"
#include "../../include/http.h"
#include <signal.h>

volatile std::atomic_int stop = std::atomic_int(0);
volatile std::atomic<app::Closable *> server;

void signal_handler(int s)
{
    std::cout << "Signal: " << s << " stop: " << stop << "\n";

    server.load()->close();
    stop++;
}

int main()
{
    using namespace std;

    try
    {
        app::SocketServer srv = app::SocketServer(8080);
        server.store(&srv);

        signal(SIGINT, signal_handler);

        while (!stop)
        {
            cout << "Wait socket connection\n";

            app::SocketClient conn = srv.waitForConnection();

            app::SocketIstream sock_in(conn.getSocket());

            app::HttpMessageParser http_parser(sock_in);

            http_parser.parse();

            std::string response = R"(
                HTTP / 1.1 200 OK
                Content-Type: text/plain
                Connection : close


                Hello, World !
        )";
            conn.writeToSocket(response);
            conn.close();
        }
    }
    catch (exception &e)
    {
        cerr << "Catch at: " << __LINE__ << ": " << typeid(e).name() << " " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    cout << "HTTP-Server shutdown";

    return 0;
}
