#include "../../../include/common.h"

namespace app
{
    void Closable::close()
    {
        doClose();
        closed = true;
    }
}
