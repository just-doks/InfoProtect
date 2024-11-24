#include "KeyHandling.h"

#include <sstream>
#include <iomanip>

namespace KH = KeyHandling;
namespace KHP = KH::__private__;

std::array<char, 8> KHP::convertKey(const std::string keyString)
{
    if (keyString.size() != 16)
        return std::array<char, 8>();

    std::array<char, 8> key{};
    unsigned char a;
    int ind = 0;
    int shift = 4;
    for (const auto ch : keyString)
    {
        a = 0;

        if (ch >= 'A' && ch <= 'F')
        {
            a = (ch - 'A') + 10;
        } else 
        if (ch >= 'a' && ch <= 'f')
        {
            a = (ch - 'a') + 10;
        } else
        if (ch >= '0' && ch <= '9')
        {
            a = ch - '0';
        }
        key[ind] |= (a << shift);
        if (shift == 0)
        {
            ++ind;
            shift = 4;            
        } else
            shift = 0;
    }
    return key;
}

#define IMPORT_KEY_FUNC(PATH) \
    std::ifstream file; \
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit); \
    std::string keybuf; \
    char ch; \
    KeyPair key; \
    try \
    { \
        file.open(PATH, std::ios_base::in); \
        if (!KHP::isProbablyKey(file)) \
            throw(KeyHandling::Exception("Key checking fail")); \
        file.seekg(0, file.beg); \
        do \
        { \
            ch = file.get(); \
            if (KHP::isCharNumber(ch)) \
                keybuf.push_back(ch); \
            else if (ch == ',') \
            { \
                key.set_key(KHP::convertKey(keybuf)); \
                keybuf.clear(); \
            } \
            else if (ch == '}') \
            { \
                key.set_iv(KHP::convertKey(keybuf)); \
                break; \
            } \
        } while (!file.eof()); \
        file.close(); \
    } \
    catch(std::ifstream::failure e) \
    { \
        throw(KeyHandling::Exception("Key importing fail")); \
    } \
    return key;


KeyPair KH::importKey(const char* path)
{
    IMPORT_KEY_FUNC(path)
}

KeyPair KH::importKey(const std::string& path)
{
    IMPORT_KEY_FUNC(path)
}

KeyPair KH::importKey(const std::string&& path)
{
    IMPORT_KEY_FUNC(path)
}

std::string KHP::getKeyString(std::array<char, 8> key, char separator) 
{
    std::stringstream ss;
    std::ios init(NULL);
    init.copyfmt(ss);
    ss << std::hex << std::uppercase; 
    ss << std::setfill('0');
    for (auto el : key)
    {
        ss << std::setw(2) << static_cast<unsigned int>
            (static_cast<unsigned char>(el));
        if (separator != 0)
            ss << separator;
    }
    ss.copyfmt(init);
    return ss.str();

}

#define EXPORT_KEY_FUNC(PATH, KEY) \
    std::ofstream file; \
    file.exceptions(std::ofstream::failbit | std::ofstream::badbit); \
    try \
    { \
        file.open(PATH, std::ios_base::out); \
        file.put('{'); \
        std::string buf = KHP::getKeyString(KEY.get_key()); \
        file.write(buf.c_str(), buf.size()); \
        file.write(", ", 2); \
        buf = KHP::getKeyString(KEY.get_iv()); \
        file.write(buf.c_str(), buf.size()); \
        file.put('}'); \
        file.close(); \
    } \
    catch(std::ifstream::failure e) \
    { \
        throw(KeyHandling::Exception("Key exporting fail")); \
    }

void KH::exportKey(const std::string& path, const KeyPair& key)
{
    EXPORT_KEY_FUNC(path, key)
}
void KH::exportKey(const std::string& path, const KeyPair&& key)
{
    EXPORT_KEY_FUNC(path, key)
}
    

bool KHP::isCharNumber(char ch)
{
    if (ch >= '0' && ch <= '9' ||
        ch >= 'a' && ch <= 'f' ||
        ch >= 'A' && ch <= 'F')
        return true;
    else
        return false;
}
bool KHP::isProbablyKey(std::ifstream& file)
{   
    if (!file.is_open())
        return false;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.seekg(0, file.end);
    size_t fsize = file.tellg();
    if (fsize > 256)
        return false;
    file.seekg(0, file.beg);

    char ch;
    int braceCnt = 0;
    int commaCnt = 0;
    int digitCnt = 0;

    for (int i = 0; i < fsize; ++i)
    {
        ch = file.get();
        if (braceCnt == 0)
        {
            if (ch == '{')
                ++braceCnt;
        }
        else
        {
            if (isCharNumber(ch))
                ++digitCnt;
            else
            if (ch == ',' && digitCnt == 16)
            {    
                ++commaCnt;
                digitCnt = 0;
            } else 
            if (ch == '}' && digitCnt == 16)
            {
                --braceCnt;
                break;
            }
        }
    }
    if (commaCnt == 1 && braceCnt == 0)
        return true;
    return false;
}

