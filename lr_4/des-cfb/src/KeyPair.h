#ifndef KEYPAIR_H
#define KEYPAIR_H

#include <array>

class KeyPair
{
    private:
        std::array<char, 8> m_key;
        std::array<char, 8> m_iv;
    public:
        KeyPair() {}
        KeyPair(std::array<char, 8> key, std::array<char, 8> iv) :
            m_key(key), m_iv(iv) {}

        KeyPair& set_key(std::array<char, 8> key)
        {
            m_key = key;
            return *this;
        }
        KeyPair& set_iv(std::array<char, 8> iv)
        {
            m_iv = iv;
            return *this;
        }
        std::array<char, 8> get_key() const
        {
            return m_key;
        }
        std::array<char, 8> get_iv() const
        {
            return m_iv;
        }
};

#endif // KEYPAIR_H