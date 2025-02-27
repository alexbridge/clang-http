#include <signal.h>
#include <functional>
#include "../../include/common.h"
#include "../../include/socket.h"
#include <atomic>
#include <vector>

int stop;
std::array<app::Closable *, 2> closables{nullptr, nullptr};

void signal_handler(int signal)
{
    std::cout << "Signal: " << signal << " stop closables: " << stop << "\n";

    for (size_t i = 0; i < closables.size(); i++)
    {
        if (closables[i])
        {
            std::cout << "Stop closable: " << closables[i] << "\n";
            closables[i]->close();
            closables[i] = nullptr;
        }
    }

    stop = signal;
}

void printClosables()
{
    std::cout << "\tClosables: ----- \n";
    for (auto closable : closables)
    {
        std::cout << "\t\tClosable: " << closable << "\n";
    }
    std::cout << "------------\n";
}

int main(int argc, char const *argv[])
{
    using namespace std;

    printClosables();

    try
    {
        app::SocketServer srv = app::SocketServer(8080);
        closables[0] = &srv;

        printClosables();

        signal(SIGINT, signal_handler);

        while (!stop)
        {
            cout << "Wait socket connection\n";

            app::SocketClient conn = srv.waitForConnection();

            cout << "Socket connected" << conn.getSocket() << "\n";

            closables[1] = &conn;

            printClosables();

            app::SocketIstream sock_in(conn.getSocket());

            std::string in;
            while (!stop)
            {
                getline(sock_in, in);

                app::utils::trim(in);

                std::string lc = std::string(in);
                std::transform(lc.begin(), lc.end(), lc.begin(), ::tolower);

                if (lc.find("exit") != std::string::npos)
                {
                    conn.writeToSocket("Bye\n");
                    break;
                }

                cout << "[" << in << "]\n";

                conn.writeToSocket("Server got: " + in + "\n");
            }

            conn.close();
            closables[1] = nullptr;

            printClosables();
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
