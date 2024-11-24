#include <iostream>
#include <fstream>
#include <vector>

int main (int argc, char* argv[])
{
    std::fstream file;
    file.open("key.txt", std::ios_base::in);
    file.seekg(std::ios_base::beg);
    /*
    char ch;
    while (file.eof())
    {
        ch = file.get();
        std::cout << ch << '\n';
    }
    */

    file.seekg(0, file.end);
    size_t sf = file.tellg();
    std::cout << "tellg = " << sf << '\n';
    file.seekg(0, file.beg);
    char ch;
    std::vector<unsigned int> v;
    

    

    ch = file.get();

    while (ch != EOF)
    {
        //v.push_back(ch - '0');
        if (ch >= '0' && ch <= '9')
            v.push_back(ch - '0');
        std::cout << static_cast<int>(ch) << ' ';
        ch = file.get();
    }
    
    
    std::cout << '\n';

     for (auto el : v)
     {
        std::cout << el;
     }
     std::cout << '\n';

    file.close();

    return 0;
}