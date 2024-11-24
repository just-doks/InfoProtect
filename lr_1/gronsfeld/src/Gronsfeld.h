#ifndef GRONSFELD_H
#define GRONSFELD_H

#include <vector>
#include <string>
#include <fstream>


//const int buffSize = 16384; // kilobytes

class Gronsfeld
{
    private:
        //static constexpr int buffSize = 16384;
        std::vector<unsigned int> m_key;
        //char sbuff[buffSize]{0};
        //char dbuff[buffSize]{0};

        //bool readKey(std::string keyPath);

        //void encryptText();
    public:
        Gronsfeld(std::vector<unsigned int> key) : m_key(key) {}

        //bool encrypt(std::string src, std::string dest);
        //void encrypt(std::string msg);

        void encrypt(char* msg, size_t msgSize);
        void decrypt(char* msg, size_t msgSize);

};

#endif // GRONSFELD_H