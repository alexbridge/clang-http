#include "../../include/utils.h"

namespace app
{
    int utils::str_to_int(std::string &str)
    {
        return utils::str_to_int(str.c_str());
    }

    int utils::str_to_int(char const *str)
    {
        try
        {
            return std::stoi(str);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error parsing str: " << str << " to int: " << e.what() << "\n";
            throw e;
        }
    }
}