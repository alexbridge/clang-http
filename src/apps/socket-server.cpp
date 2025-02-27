#include <signal.h>
#include <functional>
#include "../../include/common.h"
#include "../../include/socket.h"
#include <atomic>
#include <vector>

class SignalHandler
{
private:
    std::vector<app::Closable *> closables;

public:
    static SignalHandler *me;
    int stopSignal;

    SignalHandler(int sig, int capacity)
    {
        closables.resize(capacity);
        std::cout << "Before me\n";
        me = this;
        std::cout << "After me\n";
        signal(sig, SignalHandler::signalHandler);
    };

    void set(int index, app::Closable *closable)
    {
        closables.at(index) = closable;
    }

    void handleSignal(int signal)
    {
        std::cout << "Signal: " << signal << " stop: " << stopSignal << "\n";

        for (auto closable : closables)
        {
            if (closable)
            {
                std::cout << "Stop closable: " << closable << "\n";
                closable->close();
                closable = nullptr;
            }
        }

        closables.clear();
        stopSignal = signal;
    }

    void printClosables()
    {
        std::cout << "\tClosables " << closables.size() << ": ----- \n";
        for (auto closable : closables)
        {
            std::cout << "\t\tClosable: " << closable << "\n";
        }
        std::cout << "------------\n";
    }

    static void signalHandler(int signum)
    {
        std::cout << "signalHandler:" << me << "\n";

        me->handleSignal(signum);
    }

    SignalHandler(SignalHandler &&) = delete;
    SignalHandler(const SignalHandler &) = delete;
    SignalHandler &operator=(SignalHandler &&) = delete;
    SignalHandler &operator=(const SignalHandler &) = delete;
};

SignalHandler *SignalHandler::me;

int main(int argc, char const *argv[])
{
    using namespace std;

    cout << "Me: " << SignalHandler::me << "\n ";

    SignalHandler sigH(SIGINT, 2);
    sigH.printClosables();

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

            conn.close();
            sigH.set(1, nullptr);

            sigH.printClosables();
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
