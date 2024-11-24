#include "Gronsfeld.h"

/*
bool Gronsfeld::readKey(std::string keyPath)
{
    std::fstream keyFile;
    keyFile.open(keyPath, std::ios_base::in);
    if (!keyFile.is_open())
        return false;
    for (size_t i = 0; i < keyFile.gcount(); ++i)
        key.push_back(keyFile.get());
    return true;
}
*/

/*
void Gronsfeld::encryptText()
{
    char capitalFirst = 'A';
    char capitalLast = 'Z';
    char lowercaseFirst = 'a';
    char lowercaseLast = 'z';

    for (int i = 0, j = 0; i < buffSize; ++i, ++j)
    {
        if (sbuff[i] == 0)
            break;

        if (   !(sbuff[i] >= capitalFirst
                    && sbuff[i] <= capitalLast) 
            && !(sbuff[i] >= lowercaseFirst 
                    && sbuff[i] <= lowercaseLast))
            continue;

        if (sbuff[i] >= capitalFirst
            || sbuff[i] <= capitalLast)
        {
            if (sbuff[i] + key[j] > capitalLast)
                dbuff[i] = sbuff[i] + key[j]
                            - capitalLast + capitalFirst;
        } else
            dbuff[i] = sbuff[i] + key[j];
        if (j >= key.size())
            j = -1;
        
    }
}

bool Gronsfeld::encrypt(std::string src, std::string dest)
{
    std::fstream fileSrc, fileDest;

    fileSrc.open(src, std::ios_base::in);

    fileSrc.seekg(std::ios_base::end);
    size_t srcSize = fileSrc.tellg();
    fileSrc.seekg(std::ios_base::beg);

    fileDest.open(dest, std::ios_base::out);

    for (size_t i = 0; i < srcSize / buffSize; ++i)
    {
        fileSrc.read(sbuff, buffSize);

        encryptText();

        fileDest.write(dbuff, buffSize);
    }
    
    fileSrc.close();
    fileDest.close();
    return true;
}
*/

void Gronsfeld::encrypt(char* msg, size_t msgSize)
{
    char capitalFirst = 'A';
    char capitalLast = 'Z';
    char lowercaseFirst = 'a';
    char lowercaseLast = 'z';

    for (int i = 0, j = 0; i < msgSize; ++i)
    {
        /*
        if ((msg[i] < capitalFirst || msg[i] > capitalLast) 
            && (msg[i] < lowercaseFirst || msg[i] > lowercaseLast))
            continue;
        */

        if (msg[i] >= capitalFirst && msg[i] <= capitalLast)
        {
            if (msg[i] + m_key[j] > capitalLast)
                msg[i] = msg[i] + m_key[j] - capitalLast
                                         + capitalFirst - 1;
            else
                msg[i] = msg[i] + m_key[j];
        } else 
        if (msg[i] >= lowercaseFirst && msg[i] <= lowercaseLast)
        {
            if (msg[i] + m_key[j] > lowercaseLast)
                msg[i] = msg[i] + m_key[j] - lowercaseLast
                                         + lowercaseFirst - 1;
            else
                msg[i] = msg[i] + m_key[j];
        } else
            continue;
        if (++j == m_key.size())
            j = 0;
    }
}

void Gronsfeld::decrypt(char* msg, size_t msgSize)
{
    char capitalFirst = 'A';
    char capitalLast = 'Z';
    char lowercaseFirst = 'a';
    char lowercaseLast = 'z';

    for (int i = 0, j = 0; i < msgSize; ++i)
    {
        if (msg[i] >= capitalFirst && msg[i] <= capitalLast)
        {
            if (msg[i] - m_key[j] < capitalFirst)
                msg[i] = msg[i] - capitalFirst  + capitalLast - m_key[j] + 1;
            else
                msg[i] = msg[i] - m_key[j];
        } else 
        if (msg[i] >= lowercaseFirst && msg[i] <= lowercaseLast)
        {
            if (msg[i] - m_key[j] < lowercaseFirst)
                msg[i] = msg[i] - lowercaseFirst + lowercaseLast - m_key[j] + 1;
            else
                msg[i] = msg[i] - m_key[j];
        } else
            continue;
        if (++j == m_key.size())
            j = 0;
    }
}