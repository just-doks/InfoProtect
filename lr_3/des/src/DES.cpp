#include "DES.h"
#include "DES_functions.h"

#include <iostream>
#include <iomanip>

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

std::vector<char> DES::encrypt(std::vector<char> data, std::array<char, 8> key)
{
    size_t dSize = data.size();

    if (data.size() == 0)
        throw DESException("Data is empty");

    namespace DF = DES_functions;

    std::vector<char> dataEnc = data;

    dataEnc = DF::encrypt(data, key);   
    
    return dataEnc; //dataEnc;
}

std::vector<char> DES::decrypt(std::vector<char> data, std::array<char, 8> key) //
{
    size_t dSize = data.size();

    if (dSize == 0)
        throw DESException("Data is empty");
    if (dSize % 8 != 0)
        throw DESException("Data size is not multiple of 8");
    
    namespace DF = DES_functions;

    std::array<char, 8> T{0};
    std::vector<char> dataDec;

    dataDec = DF::decrypt(data, key);

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