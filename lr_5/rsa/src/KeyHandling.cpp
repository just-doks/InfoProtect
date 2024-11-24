#include "KeyHandling.h"
#include "MPZ.h"

namespace KH = KeyHandling;
namespace KHP = KH::__private__;

#define IMPORT_KEY_FUNC(PATH) \
    std::ifstream file; \
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit); \
    std::string keybuf; \
    char ch; \
    RSA::Key key; \
    try \
    { \
        file.open(PATH, std::ios_base::in); \
        if (!KHP::isProbablyKey(file)) \
            throw(KeyHandling::Exception("Key checking fail")); \
        file.seekg(0, file.beg); \
        do \
        { \
            ch = file.get(); \
            if (KHP::isCharNumber(ch) || ch == 'x' || ch == 'X') \
                keybuf.push_back(ch); \
            else if (ch == ',') \
            { \
                key.exp().set_str(keybuf); \
                keybuf.clear(); \
            } \
            else if (ch == '}') \
            { \
                key.mod().set_str(keybuf); \
                break; \
            } \
        } while (!file.eof()); \
        file.close(); \
    } \
    catch(std::ifstream::failure e) \
    { \
        std::cerr << "Exception opening/reading/closing file\n"; \
        throw(KeyHandling::Exception("Key importing fail")); \
    } \
    return key;


RSA::Key KH::importKey(const char* path)
{
    IMPORT_KEY_FUNC(path)
}

RSA::Key KH::importKey(const std::string& path)
{
    IMPORT_KEY_FUNC(path)
}

RSA::Key KH::importKey(const std::string&& path)
{
    IMPORT_KEY_FUNC(path)
}

#define EXPORT_KEY_FUNC(PATH, KEY) \
    std::ofstream file; \
    file.exceptions(std::ofstream::failbit | std::ofstream::badbit); \
    try \
    { \
        file.open(PATH, std::ios_base::out); \
        std::string buff = KEY.exp().get_string(-16); \
        file.write("{0x", 3); \
        file.write(buff.c_str(), buff.size()); \
        file.write(", 0x", 4); \
        buff = KEY.mod().get_string(-16); \
        file.write(buff.c_str(), buff.size()); \
        file.put('}'); \
        file.close(); \
    } \
    catch(std::ifstream::failure e) \
    { \
        std::cerr << "Exception opening/writing to/closing file\n"; \
        throw(KeyHandling::Exception("Key exporting fail")); \
    }

void KH::exportKey(const std::string& path, const RSA::Key& key)
{
    EXPORT_KEY_FUNC(path, key)
}
void KH::exportKey(const std::string& path, const RSA::Key&& key)
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
    if (fsize > 65536UL) // 64KiB
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
            if (ch == ',' && digitCnt > 0)
            {    
                ++commaCnt;
                digitCnt = 0;
            } else 
            if (ch == '}' && digitCnt > 0)
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

