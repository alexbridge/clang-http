#ifndef CLANG_COMMON_H
#define CLANG_COMMON_H

namespace app
{
    class Closable
    {
    protected:
        virtual void doClose() = 0;

    public:
        bool closed;

        void close();
    };
}

#endif