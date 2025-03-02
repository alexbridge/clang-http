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
        static SignalHandler *instance;
        std::vector<app::Closable *> closables;
        bool closeStdin = false;

    protected:
        void handleSignal(int signal);

    public:
        int stopSignal = 0;

        explicit SignalHandler(int sig, int capacity = 0, bool closeStdin = false);

        void set(int index, app::Closable *closable);

        void printClosables();

        static void signalHandler(int signum)
        {
            if (instance)
            {
                instance->handleSignal(signum);
            }
        }

        SignalHandler() = delete;
        SignalHandler(SignalHandler &&) = delete;
        SignalHandler(const SignalHandler &) = delete;
        SignalHandler &operator=(SignalHandler &&) = delete;
        SignalHandler &operator=(const SignalHandler &) = delete;
    };
}

#endif
