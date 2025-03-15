#include "../../include/utils.h"

inline auto notSpace = [](unsigned char ch)
{ return !std::isspace(ch); };

namespace app
{
    namespace utils
    {
        void trim(std::string &str)
        {

            ltrim(str);
            rtrim(str);
        }

        void ltrim(std::string &str)
        {
            str.erase(
                str.begin(),
                std::find_if(str.begin(), str.end(), notSpace));
        }
        void rtrim(std::string &str)
        {
            str.erase(std::find_if(
                          str.rbegin(),
                          str.rend(), notSpace)
                          .base(),
                      str.end());
        }

        std::string join(std::vector<std::string_view> lines, std::string_view delimiter)
        {
            std::stringstream ss;
            for (size_t i = 0; i < lines.size(); ++i)
            {
                ss << lines[i];
                if (i < lines.size() - 1)
                {
                    ss << delimiter;
                }
            }
            return ss.str();
        }
    }
}