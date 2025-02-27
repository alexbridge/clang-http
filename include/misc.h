#ifndef MISC_H
#define MISC_H

#include <vector>
#include "common.h"
#include <iostream>
#include <signal.h>

namespace app
{
    class SignalHandler
    {
    private:
        std::vector<app::Closable *> closables;

    public:
        static SignalHandler *me;
        int stopSignal;

        explicit SignalHandler(int sig, int capacity);

        void set(int index, app::Closable *closable);

        void handleSignal(int signal);

        void printClosables();

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
}

#endif
