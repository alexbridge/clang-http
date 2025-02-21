#include "utils.h"

namespace app
{
    namespace utils
    {
        int str_to_int(std::string &str)
        {
            try
            {
                return std::stoi(str);
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Error parsing str" << str << " into int: " << e.what() << std::endl;
                throw e;
            }
        }

        int str_to_int(char *str)
        {
            try
            {
                return std::stoi(str);
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << "Error parsing str" << str << " into int: " << e.what() << std::endl;
                throw e;
            }
        }
    }
}