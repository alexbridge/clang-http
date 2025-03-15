#include "../../include/utils.h"

namespace app
{
    int utils::str_to_int(const std::string_view str)
    {
        try
        {
            return std::stoi(std::string(str));
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error parsing str: " << str << " to int: " << e.what() << "\n";
            throw e;
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Out of range: " << str << " to int: " << e.what() << "\n";
            throw;
        }
    }
}