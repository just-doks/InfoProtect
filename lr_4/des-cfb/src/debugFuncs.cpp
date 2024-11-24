
#include <iostream>

std::ostream& printBinary(std::ostream& out, char letter)
{
    for (int i = 7; i >= 0; --i)
        out << static_cast<int>((letter >> i) & 1);
    out << ' ';
    return out;
}

void printCharBin(char* arr, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        printBinary(std::cout, arr[i]) << ' ';
    }
    std::cout << '\n';
}

void printChar(char* data, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        unsigned char uc = static_cast<unsigned char>(data[i]);
        std::cout << static_cast<unsigned int>(uc) << ' ';
    }
    std::cout << '\n';
}

void printByteBits(char ch)
{
    for (int i = 0; i < 8; ++i)
    {
        if (((ch << i) & 0x80) != 0)
            std::cout << '1';
        else
            std::cout << '0';
        std::cout << ' ';
    }
}

void printBits(char* data, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        printByteBits(data[i]);
        std::cout << '\n';
    }
}