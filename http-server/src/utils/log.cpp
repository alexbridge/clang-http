#include "utils.h"

namespace app
{
    namespace log
    {
        void log(const sockaddr_in &server_addr)
        {
            socklen_t client_addr_size = sizeof(struct sockaddr_in);

            char ipstr[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(server_addr.sin_addr), ipstr, sizeof(ipstr));
            std::cout << "Server:" << ipstr << "(" << client_addr_size << "): " << ntohs(server_addr.sin_port) << std::endl;
        }

        void log(const HttpRequest req)
        {
            for (auto it = req.headers.begin(); it != req.headers.end(); it++)
            {
                std::cout << it->first << " : " << it->second << std::endl;
            }
        }

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