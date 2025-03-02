#include "../../../include/misc.h"

namespace app
{
    SignalHandler *SignalHandler::instance = nullptr;

    SignalHandler::SignalHandler(int sig, int capacity, bool closeStdin) : closeStdin(closeStdin)
    {
        instance = this;

        if (capacity > 0)
        {
            closables.resize(capacity);
        }

        signal(sig, signalHandler);
    };

    void SignalHandler::set(int index, app::Closable *closable)
    {
        if (closables.capacity() <= index)
        {
            std::cerr << "Closables capacity exceed: " << closables.capacity() << "\n";
            return;
        }

        closables.at(index) = closable;
    }

    void SignalHandler::handleSignal(int signal)
    {
        std::cout << "Signal: " << signal << " stop: " << stopSignal << "\n";

        for (auto closable : closables)
        {
            if (closable && !closable->closed)
            {
                std::cout << "Close closable: " << closable << "\n";
                closable->close();
            }
        }

        closables.clear();
        std::cout << "Set stop signal: " << signal << "\n";

        stopSignal = signal;
        printClosables();

        if (closeStdin)
        {
            ::close(std::fclose(stdin));
        }
    }

    void SignalHandler::printClosables()
    {
        std::cout << "Stop signal: " << stopSignal << "\n";
        std::cout << "Close stdin: " << closeStdin << "\n";

        std::cout << "\tClosables " << closables.size() << ": ----- \n";
        for (auto closable : closables)
        {
            std::cout << "\t\tClosable: " << closable << "closed: " << (closable ? closable->closed : false) << "\n";
        }
        std::cout << "------------\n";
    }

};
