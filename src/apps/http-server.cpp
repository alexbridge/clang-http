#include <signal.h>
#include <functional>
#include "../../include/socket.h"
#include <atomic>

volatile std::atomic_int stop = std::atomic_int(0);
volatile std::atomic<app::SocketServer *> server;

void signal_handler(int s)
{
    std::cout << "Signal: " << s << " stop: " << stop << "\n";

    server.load()->close();
    stop++;
}

int main(int argc, char const *argv[])
{
    using namespace std;
    try
    {
        // Normally you'd spawn threads for multiple connections.
        app::SocketServer srv = app::SocketServer(8080);
        server.store(&srv);

        signal(SIGINT, signal_handler);

        while (!stop)
        {
            cout << "Wait socket connection\n";

            app::SocketClient conn = srv.waitForConnection();

            std::string in;
            while (!stop)
            {
                in = conn.readFromSocket();

                std::string lc = std::string(in);
                app::utils::trim(lc);
                std::transform(lc.begin(), lc.end(), lc.begin(), ::tolower);

                if (lc.find("exit") != std::string::npos)
                {
                    conn.writeToSocket("Bye\n");
                    close(conn.getSocket());
                    break;
                }

                cout << "[" << in << "]\n";

                conn.writeToSocket("Server got: " + in + "\n");
            }
        }
    }
    catch (exception &e)
    {
        cerr << "Catch at: " << __LINE__ << ": " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    cout << "Server shutdown";

    return 0;
}
