#ifndef KEYEXTRACTOR_H
#define KEYEXTRACTOR_H

#include <string>
#include <fstream>
#include <vector>
#include <exception>

#include "RSA.h"

class KeyHandler
{
    private:
        RSA::Key m_key;
        bool m_empty;
    public:
        KeyHandler() : m_empty(true) {}
        KeyHandler(const RSA::Key& key) : 
            m_key(key), 
            m_empty(false) {}
            KeyHandler(const RSA::Key&& key) : 
            m_key(key), 
            m_empty(false) {}
        
        KeyHandler& setKey(const RSA::Key& key)
        {
            m_key = key;
            m_empty = false;
            return *this;
        }
        auto getKey() const -> RSA::Key
            { return m_key; }
        auto isEmpty() -> bool 
            { return m_empty; }
        auto extractKey(std::string path) -> KeyHandler&;
        auto saveKey(std::string path) -> void;

        static RSA::Key extractKey(const std::string& path);
        static void saveKey(std::string path, RSA::Key& key);
        static void saveKey(std::string path, RSA::Key&& key);

    private:
        bool isCharNumber(char ch);
        bool isProbablyKey(std::ifstream& file);

};

class KeyHandlerException : public std::exception
{
    private:
        std::string m_error;
    public:
        KeyHandlerException(std::string msg) : m_error(msg) {}
        const char* what() const noexcept { return m_error.c_str(); }
};

namespace KeyHandling
{
    RSA::Key importKey(const char* path);
    void exportKey(std::string path, RSA::Key& key);
    void exportKey(std::string path, RSA::Key&& key);
    
    namespace __private__
    {
        bool isCharNumber(char ch);
        bool isProbablyKey(std::ifstream& file);
    }
}

#endif // KEYEXTRACTOR_H