#include <iostream>
#include <sstream>
#include "../../include/misc.h"
#include "../../include/utils.h"

int findGCD(int a, int b)
{
    if (a == 0)
    {
        return b;
    }
    return findGCD(b % a, a);
}

int main(int argc, char const *argv[])
{

    app::SignalHandler sigH(SIGINT, 0, true);
    sigH.printClosables();

    std::cout << "Start cli algorithms\n";

    while (sigH.stopSignal == 0)
    {
        std::cout << "Please enter 2 numbers separated by space to calculate GCD:\n";

        std::string line, firstStr, secondStr;

        getline(std::cin, line);

        std::istringstream ss{line};

        ss >> firstStr >> secondStr;

        try
        {
            int first, second;
            first = app::utils::str_to_int(firstStr);
            second = app::utils::str_to_int(secondStr);

            int gcd = findGCD(first, second);
            std::cout
                << "GCD(" << first << ", " << second << ") : " << gcd << "\n";
        }
        catch (const std::invalid_argument &ignore)
        {
        }
        catch (const std::exception &e)
        {
            std::cerr << typeid(e).name() << ": " << e.what() << '\n';
        }
    }

    std::cout << "By ... \n";

    return 0;
}
