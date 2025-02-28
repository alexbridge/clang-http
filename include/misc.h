#ifndef MISC_H
#define MISC_H

#include <vector>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "common.h"

namespace app
{
    class SignalHandler
    {
    private:
        std::vector<app::Closable *> closables;

    public:
        static SignalHandler *me;
        int stopSignal;
        bool closeStdin;

        explicit SignalHandler(int sig, int capacity = 0, bool closeStdin = false);

        void set(int index, app::Closable *closable);

        void handleSignal(int signal);

        void printClosables();

        static void signalHandler(int signum)
        {
            std::cout << "signalHandler:" << me << "\n";

            me->handleSignal(signum);
        }

        SignalHandler() = default;
        SignalHandler(SignalHandler &&) = delete;
        SignalHandler(const SignalHandler &) = delete;
        SignalHandler &operator=(SignalHandler &&) = delete;
        SignalHandler &operator=(const SignalHandler &) = delete;
    };
}

#endif
