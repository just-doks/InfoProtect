#ifndef DES_H
#define DES_H

#include <iostream>
#include <vector>
#include <array>

#include "DES_exception.h"

class DES
{
    public:
        enum Mode
        {
            NONE,
            ECB,
            CFB
        };
    private:
        Mode m_mode;
        std::array<char, 8> m_key;
    public:
        DES(DES::Mode mode) : m_mode(mode) {}
        std::vector<char> encrypt(std::vector<char> data, std::array<char, 8> key);
        std::vector<char> decrypt(std::vector<char> data, std::array<char, 8> key);

        auto genKey() -> std::array<char, 7>;
        auto getKey() -> std::array<char, 8>;
        auto getKeyString(char separator = 0) -> std::string;
        auto setKey(std::array<char, 8> key) -> void;

        auto extractKey(std::array<char, 8> eKey) -> std::array<char, 7>;

        //std::ostream& printKey(std::ostream& out);

};


#endif // DES_H