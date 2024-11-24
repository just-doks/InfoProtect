#ifndef GRONSFELD_H
#define GRONSFELD_H

#include <vector>
#include <string>
#include <fstream>


class Gamming
{
    private:
        std::string m_key;
    public:
        Gamming(std::string key) : m_key(key) {}

        void encrypt(char* msg, size_t msgSize);
        void decrypt(char* msg, size_t msgSize);

};

#endif // GRONSFELD_H