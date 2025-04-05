#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <sys/resource.h>
#include <cstdlib>

long long getMemoryUsage()
{
    struct rusage usage;
    if (getrusage(RUSAGE_SELF, &usage) == 0)
    {
        return usage.ru_maxrss * 1024; // in bytes
    }
    return -1; // Error
}

std::string hMem(long long &mem)
{
    char buffer[100];
    std::sprintf(buffer, "%lld kb", mem / 1024);
    return std::string(buffer);
}

void fatMethod(int size)
{
    std::vector<int> data(size);
    for (int i = 0; i < size; ++i)
    {
        data[i] = std::rand();
    }
    long long sum = 0;
    for (int x : data)
    {
        sum += x;
    }
    std::cout << "Sum: " << sum << std::endl;
}

int main(int argc, char const *argv[])
{

    std::cout << "Start CLI-IO" << std::endl;
    std::string inPath = "plain_text.txt";
    std::string outPath = "plain_text_copy.txt";

    std::remove(outPath.c_str());

    std::ifstream in(inPath, std::ios::binary);
    if (!in.is_open())
    {
        std::cerr << "Error: Unable to open source file: " << inPath << std::endl;
        return 1;
    }

    std::ofstream out(outPath, std::ios::binary);
    if (!out.is_open())
    {
        std::cerr << "Error: Unable to open destination file: " << outPath << std::endl;
        in.close();
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    auto startMemory = getMemoryUsage();

    size_t bufferSize = 16 * 1024;
    char buffer[bufferSize];

    while (in.read(buffer, bufferSize))
    {
        out.write(buffer, in.gcount());
    }

    if (in.gcount() > 0)
    {
        out.write(buffer, in.gcount());
    }

    if (in.bad() || out.bad())
    {
        std::cerr << "Error: File copy failed due to read/write error." << std::endl;
        in.close();
        out.close();
        return 1;
    }

    in.close();
    out.close();

    // fatMethod(10'000'000);

    auto end = std::chrono::high_resolution_clock::now();
    auto endMemory = getMemoryUsage();

    auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    auto mem = endMemory - startMemory;

    std::cout << "Copied in " << (dur) << "ms" << std::endl;
    std::cout << "Memory: start " << hMem(startMemory) << ", end " << hMem(endMemory) << ", used " << hMem(mem) << std::endl;

    /**
     * Copied in 214ms
     * Memory: start 16592 kb, end 16592 kb, used 0 kb
     */

    return 0;
}
