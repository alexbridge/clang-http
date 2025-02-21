#include "utils.h"

namespace app
{
    namespace utils
    {
        long long usedRem()
        {
            struct sysinfo info;
            sysinfo(&info);

            std::string str = "foo-bar";

            for (size_t i = 0; i < 20; i++)
            {
                str.append(str.begin(), str.end());
            }

            return info.freeram * info.mem_unit / 1024 / 1024;
        }
    }
}