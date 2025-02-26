#include <signal.h>
#include <functional>
#include "../../include/common.h"
#include "../../include/socket.h"
#include <atomic>
#include <vector>

volatile std::atomic_int stop = std::atomic_int(0);
volatile std::atomic<app::Closable *> server;
volatile std::atomic<app::Closable *> client;

void signal_handler(int s)
{
    std::cout << "Signal: " << s << " stop: " << stop << "\n";

    auto cl = client.load();
    if (cl)
    {
        cl->close();
    }

    server.load()->close();

    stop++;
}

int main(int argc, char const *argv[])
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

            client.store(&conn);

            cout << "Socket connected" << conn.getSocket() << "\n";

            app::SocketIstream sock_in(conn.getSocket());

            std::string in;
            while (!stop)
            {
                getline(sock_in, in);
                std::cout << in << "\n";

                app::utils::trim(in);

                std::string lc = std::string(in);
                std::transform(lc.begin(), lc.end(), lc.begin(), ::tolower);

                if (lc.find("exit") != std::string::npos)
                {
                    conn.writeToSocket("Bye\n");
                    conn.close();
                    break;
                }

                cout << "[" << in << "]\n";

                conn.writeToSocket("Server got: " + in + "\n");
            }
        }
    }
    catch (exception &e)
    {
        cerr << "Catch at: " << __LINE__ << ": " << typeid(e).name() << " " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    cout << "Server shutdown";

    return 0;
}
