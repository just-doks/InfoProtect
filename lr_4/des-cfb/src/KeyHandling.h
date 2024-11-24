#ifndef KEYHANDLING_H
#define KEYHANDLING_H

#include <string>
#include <fstream>
#include <exception>
#include <array>

#include "KeyPair.h"

namespace KeyHandling
{
    KeyPair importKey(const char* path);
    KeyPair importKey(const std::string& path);
    KeyPair importKey(const std::string&& path);
    void exportKey(const std::string& path, const KeyPair& key);
    void exportKey(const std::string& path, const KeyPair&& key);
    
    class Exception : public std::exception
    {
        private:
            std::string m_error;
        public:
            Exception(std::string msg) : m_error(msg) {}
            const char* what() const noexcept { return m_error.c_str(); }
    };

    namespace __private__
    {
        bool isCharNumber(char ch);
        bool isProbablyKey(std::ifstream& file);
        std::array<char, 8> convertKey(const std::string keyString);
        std::string getKeyString(std::array<char, 8> key, char separator = 0);
    }
}

#endif // KEYHANDLING_H