#include "KeyHandler.h"

bool KeyHandler::isCharNumber(char ch)
{
    if (ch >= '0' && ch <= '9' ||
        ch >= 'a' && ch <= 'f' ||
        ch >= 'A' && ch <= 'F')
        return true;
    else
        return false;
}

bool KeyHandler::isProbablyKey(std::ifstream& file)
{   
    if (!file.is_open())
        return false;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.seekg(0, file.end);
    size_t fsize = file.tellg();
    if (fsize > 65536)
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
        else //if (braces.size())
        {
            if (isCharNumber(ch))
                ++digitCnt;
            else
            if (ch == ',' && digitCnt > 0)  // && chprev != '{')
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

KeyHandler& KeyHandler::extractKey(std::string path)
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::string keybuf;
    char ch;
    //RSA::Key key;
    try
    {
        file.open(path, std::ios_base::in);
        if (!isProbablyKey(file))
            throw(KeyHandlerException("Key checking fail"));
        file.seekg(0, file.beg);
        do
        {
            ch = file.get();
            if (isCharNumber(ch) || ch == 'x' || ch == 'X')
                keybuf.push_back(ch);
            else if (ch == ',')
            {
                m_key.exponent.set_str(keybuf);
                keybuf.clear();
            }
            else if (ch == '}')
            {
                m_key.modulus.set_str(keybuf);
                break;
            }
        } while (!file.eof());
        file.close();
    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "Exception opening/reading/closing file\n";
        throw(KeyHandlerException("Key extracting fail"));
    }
    return *this;
}

#define SAVEKEY_FUNC(KEY) \
    std::ofstream file; \
    file.exceptions(std::ofstream::failbit | std::ofstream::badbit); \
    try \
    { \
        file.open(path, std::ios_base::out); \
        std::string buff; \ 
        buff = KEY.exponent.getString(10); \
        file.put('{'); \
        file.write(buff.c_str(), buff.size()); \
        file.write(", 0x", 4); \
        buff = KEY.modulus.getString(-16); \
        file.write(buff.c_str(), buff.size()); \
        file.put('}'); \
        file.close(); \
    } \
    catch(std::ifstream::failure e) \
    { \
        std::cerr << "Exception opening/writing to/closing file\n"; \
        throw(KeyHandlerException("Key saving fail")); \
    }

void KeyHandler::saveKey(std::string path)
{
    SAVEKEY_FUNC(m_key)
}

void saveKey(std::string path, RSA::Key& key)
{
    SAVEKEY_FUNC(key)
}

void saveKey(std::string path, RSA::Key&& key)
{
    SAVEKEY_FUNC(key)
}

