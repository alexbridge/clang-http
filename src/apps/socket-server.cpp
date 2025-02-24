#include "../../include/socket.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    try
    {
        // Normally you'd spawn threads for multiple connections.
        app::SocketServer srv = app::SocketServer(8080);

        while (true)
        {
            cout << "Start socket server" << endl;

            app::SocketClient conn = srv.waitForConnection();

            std::string in;
            while (true)
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
    catch (runtime_error &e)
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    return 0;
}
