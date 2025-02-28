#include <iostream>
#include <sstream>
#include "../../include/misc.h"
#include "../../include/utils.h"

int realGcd(int left, int right)
{
    // 130 mod 70
    int remainder = left % right;
    if (remainder <= 0)
    {
        return right;
    }
    // 70 mod 60
    // 60 mod 10 => 6
    return realGcd(right, remainder);
}

int gcd(int left, int right)
{
    if (left == right)
    {
        return left;
    }

    if (left > right)
    {
        return realGcd(left, right);
    }
    return realGcd(right, left);
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
            std::cout
                << "GCD(" << first << ", " << second << ") : " << gcd(first, second) << "\n";
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
