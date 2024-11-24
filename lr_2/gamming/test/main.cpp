#include <iostream>
#include <fstream>

std::ostream& printBinary(std::ostream& out, char letter)
{
    for (int i = 7; i >= 0; --i)
        out << static_cast<int>((letter >> i) & 1);
    out << ' ';
    return out;
}

int main(int argc, char* argv[])
{   
    char x = 'A';
    char k = 'B';

    char cstr[1] = {'A'};
    std::string str{"B"};

    printBinary(std::cout, cstr[0]) << '\n';
    printBinary(std::cout, str[0]) << '\n';
    printBinary(std::cout, cstr[0] ^ str[0]) << '\n';

    std::ofstream ofile;
    ofile.open("file.bin", std::ios_base::out | std::ios_base::binary);

    cstr[0] = cstr[0] ^ str[0]; 

    ofile.write(cstr, 1);
    ofile.close();

    std::ifstream ifile;
    ifile.open("file.bin", std::ios_base::in | std::ios_base::binary);

    char* buff = new char[10]{0};

    ifile.read(buff, 1);
    ifile.close();

    buff[0] = buff[0] ^ str[0];

    ofile.open("file.txt", std::ios_base::out);
    ofile.write(buff, 1);
    ofile.close();
    delete[] buff;

    /*
    std::cout << static_cast<int>(x ^ k) << '\n';

    printBinary(x);
    std::cout << '\n';
    printBinary(k);
    std::cout << '\n';
    printBinary(x ^ k);
    std::cout << '\n';
    */


    return 0;    
}