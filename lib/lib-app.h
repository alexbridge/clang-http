#ifndef lib_app_H
#define lib_app_H

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

namespace app
{
    void simpleMath()
    {
        int foo = 1;
        int bar = 2;

        printf("Foo %d + Bar %d = %d\n", foo, bar, (foo + bar));
    }

    void simpleInput()
    {
        cout << "Input: ";

        string line;
        getline(cin, line);

        printf("Output: %s (%ld)\n", line.c_str(), line.length());
    }
}
#endif