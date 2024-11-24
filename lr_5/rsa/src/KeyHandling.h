#ifndef KEYHANDLING_H
#define KEYHANDLING_H

#include <string>
#include <fstream>
#include <exception>

#include "RSA.h"

namespace KeyHandling
{
    RSA::Key importKey(const char* path);
    RSA::Key importKey(const std::string& path);
    RSA::Key importKey(const std::string&& path);
    void exportKey(const std::string& path, const RSA::Key& key);
    void exportKey(const std::string& path, const RSA::Key&& key);
    
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
    }
}

#endif // KEYHANDLING_H