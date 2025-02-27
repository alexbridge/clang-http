#include "../../../include/misc.h"

namespace app
{
    SignalHandler *SignalHandler::me;

    SignalHandler::SignalHandler(int sig, int capacity)
    {
        closables.resize(capacity);
        me = this;
        signal(sig, SignalHandler::signalHandler);
    };

    void SignalHandler::set(int index, app::Closable *closable)
    {
        closables.at(index) = closable;
    }

    void SignalHandler::handleSignal(int signal)
    {
        std::cout << "Signal: " << signal << " stop: " << stopSignal << "\n";

        for (auto closable : closables)
        {
            if (closable)
            {
                std::cout << "Stop closable: " << closable << "\n";
                closable->close();
            }
        }

        closables.clear();
        stopSignal = signal;
    }

    void SignalHandler::printClosables()
    {
        std::cout << "\tClosables " << closables.size() << ": ----- \n";
        for (auto closable : closables)
        {
            std::cout << "\t\tClosable: " << closable << "\n";
        }
        std::cout << "------------\n";
    }

};
