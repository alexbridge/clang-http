#include <atomic>
#include <signal.h>
#include "../../include/socket.h"
#include "../../include/http.h"
#include "../../include/misc.h"

int main()
{
    using namespace std;

    app::SignalHandler sigH(SIGINT, 2);
    sigH.printClosables();

    std::atomic_int requests(1);

    try
    {
        app::SocketAddressIn addressIn{"0.0.0.0", 8080};
        app::SocketServer srv = app::SocketServer(addressIn);

        sigH.set(0, &srv);

        while (!sigH.stopSignal)
        {
            auto conn = srv.waitForConnection();
            std::cout << "\t == new socket connection: " << conn.get()->sockFd << "of " << requests.load() << "\n";

            requests++;

            std::thread clientThread(app::HttpHandler::handle, std::move(conn));
            clientThread.detach();
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
