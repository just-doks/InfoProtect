#ifndef __RSA_H__
#define __RSA_H__

#include "MPZ.h"
#include <vector>
#include <exception> // std::exception
#include <cstdint> // uint64_t

class RSA
{
    public:
        class Key
        {
            private:
            MPZ exponent;
            MPZ modulus;

            public:
            Key() {}
            Key(const Key& key);
            Key(const MPZ& exp, const MPZ& mod);

            auto exp() const -> const MPZ&;
            auto exp() -> MPZ&;
            auto exp(const MPZ& exp) -> void;
            auto mod() const -> const MPZ&;
            auto mod() -> MPZ&;
            auto mod(const MPZ& mod) -> void;

            Key& operator=(const Key& key);
        };

        RSA() {}
        ~RSA() {}

        auto genKeys(int bits, unsigned long exp) -> bool;
        auto encrypt(const std::vector<char>& data, const Key& key) -> std::vector<char>;
        auto decrypt(const std::vector<char>& data, const Key& key) -> std::vector<char>;
        auto getPrivateKey() -> Key;
        auto getPublicKey() -> Key;
        auto pub() -> Key;
        auto priv() -> Key;

    private:
        MPZ m_E;
        MPZ m_D;
        MPZ m_N;

        MPZ makeprime(int bits, unsigned long e);
        uint64_t getRandomNumber(uint64_t min, uint64_t max);
};

class RSA_Exception : public std::exception
{
    private:
        std::string m_error;
    public:
        RSA_Exception(std::string msg) : m_error(msg) {}
        const char* what() const noexcept { return m_error.c_str(); }
};

#endif // RSA_H