#include <signal.h>
#include <functional>
#include "../../include/socket.h"

volatile sig_atomic_t stop{0};

inline std::function<void()> shutdown_handler;
inline void signal_handler(int s)
{
    std::cout << "Signal: " << s << " stop: " << stop << std::endl;
    shutdown_handler();
    stop = 1;
}

int main(int argc, char const *argv[])
{
    using namespace std;
    try
    {
        // Normally you'd spawn threads for multiple connections.
        app::SocketServer srv = app::SocketServer(8080);

        auto shutdown_handler = [&srv]()
        {
            cout << "Server shutdown...\n";
            // srv.close();
        };

        signal(SIGINT, signal_handler);

        while (!stop)
        {
            cout << "Wait socket connection" << endl;

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

                cout << "[" << in << "]" << endl;

                conn.writeToSocket("Server got: " + in + "\n");
            }
        }
    }
    catch (exception &e)
    {
        cerr << "Catch at: " << __LINE__ << ": " << e.what() << endl;
        return EXIT_FAILURE;
    }
    return 0;
}
