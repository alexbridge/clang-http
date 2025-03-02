#include <iostream>

class MyClass
{
public:
    int myInt1;
    double myDouble1;
    bool myBool1;
    int myInt2 = 0;
    double myDouble2 = 0.0;
    bool myBool2 = true;
    int myInt3;
    double myDouble3;
    bool myBool3;

    void printValues()
    {
        std::cout << "myInt1: " << myInt1 << std::endl;
        std::cout << "myDouble1: " << myDouble1 << std::endl;
        std::cout << "myBool1: " << myBool1 << std::endl;
        std::cout << " === Initialization list ===" << std::endl;
        std::cout << "myInt2: " << myInt2 << std::endl;
        std::cout << "myDouble2: " << myDouble2 << std::endl;
        std::cout << "myBool2: " << myBool2 << std::endl;
        std::cout << " === Curly braces === " << std::endl;
        std::cout << "myInt3: " << myInt3 << std::endl;
        std::cout << "myDouble3: " << myDouble3 << std::endl;
        std::cout << "myBool3: " << myBool3 << std::endl;
    }
};

int main()
{
    std::cout << "------------------" << std::endl;
    MyClass obj;
    obj.printValues(); // Output: Unpredictable values
    std::cout << "------------------" << std::endl;

    std::cout << "------------------" << std::endl;
    MyClass obj2;
    obj2.printValues(); // Output: Unpredictable values
    std::cout << "------------------" << std::endl;
    return 0;
}