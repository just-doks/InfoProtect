#include "Gamming.h"


void Gamming::encrypt(char* msg, size_t msgSize)
{
    //char firstSymbol = 32;
    //char lastSymbol = 126;

    for (int i = 0, j = 0; i < msgSize; ++i)
    {
        //if (msg[i] >= firstSymbol && msg[i] <= lastSymbol)
        msg[i] = (msg[i] ^ m_key[j]);
        //else 
        //    continue;
        if (++j == m_key.size())
            j = 0;
    }
}

void Gamming::decrypt(char* msg, size_t msgSize)
{
    for (int i = 0, j = 0; i < msgSize; ++i)
    {
        msg[i] = (msg[i] ^ m_key[j]);
        if (++j == m_key.size())
            j = 0;
    }
}