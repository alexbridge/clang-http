#include <signal.h>
#include <functional>
#include "../../include/common.h"
#include "../../include/socket.h"
#include "../../include/misc.h"
#include <atomic>
#include <vector>

int main(int argc, char const *argv[])
{
    using namespace std;

    cout << "Me: " << app::SignalHandler::me << "\n ";

    app::SignalHandler sigH(SIGINT, 2);
    sigH.printClosables();

    cout << "Me after: " << app::SignalHandler::me << "\n ";

    try
    {
        app::SocketServer srv = app::SocketServer(8080);
        cout << "Before set\n";
        sigH.set(0, &srv);
        cout << "AFter set\n";

        sigH.printClosables();

        while (!sigH.stopSignal)
        {
            cout << "Wait socket connection\n";

            app::SocketClient conn = srv.waitForConnection();

            cout << "Socket connected" << conn.getSocket() << "\n";

            sigH.set(1, &conn);

            sigH.printClosables();

            app::SocketIstream sock_in(conn.getSocket());

            std::string in;
            while (!sigH.stopSignal)
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

            std::cout << "Client stop and remove\n";

            if (!conn.closed)
            {
                conn.close();
                sigH.set(1, nullptr);
                sigH.printClosables();
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
