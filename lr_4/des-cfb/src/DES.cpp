#include "DES.h"
#include "DES_functions.h"
#include "Constants.h"

#include <iostream>
#include <iomanip>
#include <sstream> // std::basic_stringstream

std::array<char, 7> DES::genKey()
{
    namespace DF = DES_functions;
    std::array<char, 7> key = DF::genKey();
    m_key = DF::expandKey(key);
    return key;
}
std::array<char, 8> DES::getKey()
{
    if (m_key.size() == 0)
        throw DESException("Key is not generated");
    return m_key;
}
void DES::setKey(std::array<char, 8> key)
{
    m_key = key;
}

std::vector<char> DES::encrypt(std::vector<char> data)
{
    size_t dSize = data.size();

    if (data.size() == 0)
        throw DESException("Data is empty");

    namespace DF = DES_functions;

    std::vector<char> dataEnc; //= data;

    dataEnc = DF::encrypt(data, m_key);   
    
    return dataEnc; //dataEnc;
}

std::vector<char> DES::encrypt_cfb(std::vector<char> data)
{
    namespace DF = DES_functions;
    size_t dSize = data.size();

    if (dSize == 0)
        return std::vector<char>();

    std::vector<char> dataEnc;
    std::array<char, 8> T;

    size_t boundary;
    if (dSize % 8 == 0)
        boundary = dSize / 8;
    else
        boundary = dSize / 8 + 1;
    
    T = m_iv;
    for (int i = 0; i < boundary; ++i)
    {
        // DES -------
        T = DF::permutation(T, Constants::IP);
        T = DF::encryption(T, m_key);
        T = DF::permutation(T, Constants::IP_reverse);
        // -----------

        // C_i = M_i xor Z_i, Z_i = DES(C_i-1), C_0 = IV
        for (int j = 0; j < 8; ++j)
        {
            if (i * 8 + j < dSize)
                T[j] = T[j] ^ data[i * 8 + j];
            else
                T[j] = T[j] ^ 0u;
            dataEnc.push_back(T[j]);
        }
    }
    return dataEnc;
}

std::vector<char> DES::decrypt_cfb(std::vector<char> data)
{
    size_t dSize = data.size();

    if (dSize == 0 || dSize % 8 != 0)
        return std::vector<char>();

    std::vector<char> dataDec;
    std::array<char, 8> T;

    namespace DF = DES_functions;
    
    T = m_iv;
    for (int i = 0; i < dSize / 8; ++i)
    {
        // DES -----------
        T = DF::permutation(T, Constants::IP);
        T = DF::encryption(T, m_key); // GENIOUS !!!
        //T = DF::decryption(T, m_key);
        T = DF::permutation(T, Constants::IP_reverse);
        // ---------------

        // M_i = C_i xor Z_i, Z_i = DES(C_i-1), C_0 = IV
        for (int j = 0; j < 8; ++j)
        {
            dataDec.push_back(T[j] ^ data[i * 8 + j]);
            T[j] = data[i * 8 + j];
        }
    }
    return dataDec;
}

std::vector<char> DES::decrypt(std::vector<char> data) //
{
    size_t dSize = data.size();

    if (dSize == 0)
        throw DESException("Data is empty");
    if (dSize % 8 != 0)
        throw DESException("Data size is not multiple of 8");
    
    namespace DF = DES_functions;

    //std::array<char, 8> T{0};
    std::vector<char> dataDec;

    dataDec = DF::decrypt(data, m_key);

    return dataDec;
}

std::array<char, 7> DES::extractKey(std::array<char, 8> eKey)
{
    namespace DF = DES_functions;
    return DF::extractKey(eKey);
}

std::string DES::getKeyString(char separator) 
{
    std::stringstream ss;
    std::ios init(NULL);
    init.copyfmt(ss);
    ss << std::hex << std::uppercase; 
    ss << std::setfill('0');
    for (auto el : m_key)
    {
        ss << std::setw(2) << static_cast<unsigned int>
            (static_cast<unsigned char>(el));
        if (separator != 0)
            ss << separator;
    }
    ss.copyfmt(init);
    return ss.str();

}

std::array<char, 8> DES::genIV()
{
    namespace DF = DES_functions;
    std::array<char, 8> iv{};
    for (int i = 0; i < 8; ++i)
    {
        iv[i] |= DF::getRandomNumber(0x0, 0xFF);
    }
    m_iv = iv;
    return iv;
}

KeyPair DES::getKeyPair()
{
    if (m_key.size() == 0)
        genKey();
    if (m_iv.size() == 0)
        genIV();
    return KeyPair(m_key, m_iv);
}

DES& DES::setKeyPair(KeyPair& pair)
{
    m_key = pair.get_key();
    m_iv = pair.get_iv();
    return *this;
}