#include "../../include/socket.h"
#include "../../include/misc.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    app::SignalHandler sigH(SIGINT, 2);
    sigH.printClosables();

    cout << "Init signal handler: " << sigH.stopSignal << "\n ";

    try
    {
        app::SocketAddressIn addressIn{"0.0.0.0", 8080};

        app::SocketServer srv = app::SocketServer(addressIn);

        sigH.set(0, &srv);
        sigH.printClosables();

        while (!sigH.stopSignal)
        {
            cout << "Wait socket connection\n";

            auto conn = srv.waitForConnection();

            sigH.set(1, conn.get());
            sigH.printClosables();

            app::SocketStreambuf sock_in(conn.get()->sockFd);

            std::istream socketStream(&sock_in);

            std::string in;
            while (!sigH.stopSignal)
            {
                getline(socketStream, in);

                app::utils::trim(in);

                std::string lc = std::string(in);
                std::transform(lc.begin(), lc.end(), lc.begin(), ::tolower);

                if (lc.find("exit") != std::string::npos)
                {
                    conn.get()->writeToSocket("Bye\n");
                    break;
                }

                cout << "[" << in << "]\n";

                conn->writeToSocket("Server got: " + in + "\n");
            }

            std::cout << "Client stop and remove\n";

            if (!conn.get()->closed)
            {
                conn.get()->close();
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
