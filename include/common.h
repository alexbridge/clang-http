#ifndef CLANG_COMMON_H
#define CLANG_COMMON_H

namespace app
{
    class Closable
    {
    public:
        virtual void close() = 0;
    };
}

#endif