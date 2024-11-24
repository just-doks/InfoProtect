#include <array>
#include <iostream>
#include <random> // C++11, std::random_device, std::mt19937 

#include "Constants.h"
#include "DES_functions.h"

namespace DES_functions
{

std::ostream& printBinary(std::ostream& out, char letter)
{
    for (int i = 7; i >= 0; --i)
        out << static_cast<int>((letter >> i) & 1);
    out << ' ';
    return out;
}

std::array<char, 8> initialPermutation(std::array<char, 8> T)
{
    using namespace Constants;
    std::array<char, 8> T0;
    for (int i = 0; i < 8; ++i)
    {
        T0[i] = 0;
        for (int j = 0; j < 8; ++j)
        {
            int byte = (IP[i * 8 + j] - 1) / 8;
            int bit = (IP[i * 8 + j] - 1) - (byte * 8);
            T0[i] |= ((T[byte] << bit) & 0x80) >> j;
        }
    }
    return T0;
}

std::array<char, 8> permutation(std::array<char, 8> T, std::array<int, 64> IP)
{
    std::array<char, 8> TP;
    for (int i = 0; i < 8; ++i)
    {
        TP[i] = 0;
        for (int j = 0; j < 8; ++j)
        {
            int byte = (IP[i * 8 + j] - 1) / 8;
            int bit = (IP[i * 8 + j] - 1) - (byte * 8);
            TP[i] |= ((T[byte] << bit) & 0x80) >> j;
        }
    }
    return TP;
}

std::array<char, 4> getL(std::array<char, 8> T)
{
    std::array<char, 4> L;
    for (int i = 0; i < 4; ++i)
        L[i] = T[i];
    return L;
}

std::array<char, 4> getR(std::array<char, 8> T)
{
    std::array<char, 4> R;
    for (int i = 4, j = 0; i < 8; ++i, ++j)
        R[j] = T[i];
    return R;
}

std::array<char, 6> expand(std::array<char, 4> RorL)
{
    using Constants::E;
    std::array<char, 6> RorLE;
    for (int i = 0; i < 6; ++i)
    {
        RorLE[i] = 0;
        for (int j = 0; j < 8; ++j)
        {
            int byte = (E[i * 8 + j] - 1) / 8;
            int bit = (E[i * 8 + j] - 1) - (byte * 8);
            RorLE[i] |= ((RorL[byte] << bit) & 0x80) >> j;
        }
    }
    return RorLE;
}

std::array<char, 6> xor48(std::array<char, 6> RorLE, std::array<char, 6> K)
{
    std::array<char, 6> RorLEK;
    for (int i = 0; i < 6; ++i)
        RorLEK[i] = RorLE[i] ^ K[i];
    return RorLEK;
}

std::array<char, 8> getB(std::array<char, 6> RorLEK)
{
    std::array<char, 8> B;
    int  ind = 0, bitShift = 8;
    for (int i = 0; i < 8; ++i)
    {
        B[i] = 0;
        for (int j = 5; j >= 0; --j)
        { 
            B[i] |= ((RorLEK[ind] >> --bitShift) & 0x1) << j;
            if (bitShift == 0)
            {
                ++ind;
                bitShift = 8;
            }
        }
    }
    return B;
}

std::array<char, 4> shrink(std::array<char, 8> B)
{
    std::array<char, 4> BS{};
    using Constants::S;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {   
            int ind = i * 2 + j;
            int row = ( ((B[ind] >> 4) & 0x2) | (B[ind] & 0x1) ); // Строка
            int column = ((B[ind] >> 1) & 0xF); // столбец
            
            BS[i] |= S[ind][row][column] << (4 - 4 * j);
        }
    }
    return BS;
}

std::array<char, 4> transposition(std::array<char, 4> BS)
{
    std::array<char, 4> BST;
    using Constants::P;
    for (int i = 0; i < 4; ++i)
    {
        BST[i] = 0;
        for (int j= 0; j < 8; ++j)
        {
            int byte = (P[i * 8 + j] - 1) / 8;
            int bit = (P[i * 8 + j] - 1) - (byte * 8);
            BST[i] |= ((BS[byte] << bit) & 0x80) >> j;
        }
    }
    return BST;
}

std::array<char, 4> f(std::array<char, 4> RorL, std::array<char, 6> K)
{
    std::array<char, 6> RorLE = expand(RorL);

    std::array<char, 6> RorLEK = xor48(RorLE, K);

    std::array<char, 8> B = getB(RorLEK);

    std::array<char, 4> BS = shrink(B); 

    std::array<char, 4> BST = transposition(BS);

    return BST;
}

std::array<char, 8> combineLR(std::array<char, 4> L, std::array<char, 4> R)
{
    std::array<char, 8> C;
    for (int i = 0; i < 4; ++i)
    {
        C[i] = L[i];
        C[4 + i] = R[i];
    }
    return C;
}

std::array<char, 7> prepareKey(std::array<char, 8> key)
{
    using Constants::G;
    std::array<char, 7> CD{};

    for (int i = 0; i < 7; ++i)
    {
        for (int j= 0; j < 8; ++j)
        {
            int byte = (G[i * 8 + j] - 1) / 8;
            int bit = (G[i * 8 + j] - 1) % 8; //- (byte * 8);
            CD[i] |= ((key[byte] << bit) & 0x80) >> j;
        }    
    }
    return CD;
}

std::array<char, 7> shiftCD(std::array<char, 7> CD, int shift)
{
    std::array<char, 7> CDS{};
    int counter = 0;

    int CDSbyte, CDSbit, CDbyte, CDbit;

    for (int i = 0; i < 28; ++i)
    {
        CDSbyte = i / 8;
        CDSbit = i % 8;
        if (i + shift < 28)
        {
            CDbyte = (i + shift) / 8; 
            CDbit = (i + shift) % 8;
        } else
        {
            CDbyte = (i + shift - 28) / 8; 
            CDbit = (i + shift - 28) % 8;
        }
        CDS[CDSbyte] |= ((CD[CDbyte] << CDbit) & 0x80) >> CDSbit; 
    }

    for (int i = 28; i < 56; ++i)
    {
        CDSbyte = i / 8;
        CDSbit = i % 8;
        if (i + shift < 56)
        {
            CDbyte = (i + shift) / 8; 
            CDbit = (i + shift) % 8;
        } else
        {
            CDbyte = (i + shift - 28) / 8; 
            CDbit = (i + shift - 28) % 8;
        }
        CDS[CDSbyte] |= ((CD[CDbyte] << CDbit) & 0x80) >> CDSbit; 
    }
    return CDS;
}

std::array<char, 6> getK(std::array<char, 7> CDS)
{
    using Constants::H;
    std::array<char, 6> K{};
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            int byte = (H[i * 8 + j] - 1) / 8;
            int bit = (H[i * 8 + j] - 1) % 8;
            K[i] |= ((CDS[byte] << bit) & 0x80) >> j;
        }
    }
    return K;
}

std::array<char, 8> encryption(std::array<char, 8> TP, std::array<char, 8> key)
{
    using Constants::shift;
    std::array<char, 7> CiDi = prepareKey(key);
    std::array<char, 6> K;
    std::array<char, 4> Lprev, L = getL(TP);
    std::array<char, 4> R = getR(TP);

    for (int i = 0; i < 16; ++i)
    {
        CiDi = shiftCD(CiDi, shift[i]);
        K = getK(CiDi);
        Lprev = L;
        L = R;
        R = f(R, K);
        for (int j = 0; j < 4; ++j)
            R[j] = Lprev[j] ^ R[j];
    } // Проверить, что получается на выходе!

    std::array<char, 8> C = combineLR(L, R);
    return C;
}

std::array<char, 8> decryption(std::array<char, 8> revTP, std::array<char, 8> key)
{
    using Constants::shift;
    std::array<char, 7> CiDi = prepareKey(key);
    std::array<char, 6> K;
    std::array<char, 4> L = getL(revTP);
    std::array<char, 4> Rprev, R = getR(revTP);

    /*
    for (int i = 0; i < 16; ++i)
    {
        CiDi = shiftCD(CiDi, shift[i]);
    } */ // Шаг логически не обоснован

    for (int i = 15; i >= 0; --i)
    //for (int i = 0; i < 16; ++i)
    {
        K = getK(CiDi); // Сравнить генерируемые здесь ключи с ключами из encryption() !
        CiDi = reverseShiftCD(CiDi, shift[i]); // Возможно, это неверно
        //CiDi = shiftCD(CiDi, shift[i]); // Тогда, это верный вариант
        // K = getK(CiDi); // Сравнить генерируемые здесь ключи с ключами из encryption() !
        Rprev = R;
        R = L;
        L = f(L, K);
        for (int j = 0; j < 4; ++j)
            L[j] = Rprev[j] ^ L[j];
    }

    std::array<char, 8> C = combineLR(L, R);
    return C;
}

std::array<char, 7> reverseShiftCD(std::array<char, 7> CD, int shift)
{
    std::array<char, 7> CDS{};
    int counter = 0;

    int CDSbyte, CDSbit, CDbyte, CDbit;

    for (int i = 0; i < 28; ++i)
    {
        CDSbyte = i / 8;
        CDSbit = i % 8;
        if (i - shift >= 0)
        {
            CDbyte = (i - shift) / 8; 
            CDbit = (i - shift) % 8;
        } else
        {
            CDbyte = (i - shift + 28) / 8; 
            CDbit = (i - shift + 28) % 8;
        }
        CDS[CDSbyte] |= ((CD[CDbyte] << CDbit) & 0x80) >> CDSbit; 
    }

    for (int i = 28; i < 56; ++i)
    {
        CDSbyte = i / 8;
        CDSbit = i % 8;
        if (i - shift >= 28)
        {
            CDbyte = (i - shift) / 8; 
            CDbit = (i - shift) % 8;
        } else
        {
            CDbyte = (i - shift + 28) / 8; 
            CDbit = (i - shift + 28) % 8;
        }
        CDS[CDSbyte] |= ((CD[CDbyte] << CDbit) & 0x80) >> CDSbit; 
    }
    return CDS;
}

std::vector<char> encrypt(std::vector<char>& data, std::array<char, 8> key)
{
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
    
    for (int i = 0; i < boundary; ++i)
    {
        T = {};
        for (int j = 0; j < 8; ++j)
        {
            if (i * 8 + j < dSize)
                T[j] = data[i * 8 + j];
            else
                T[j] = 0;
        }
        // DES-ECB encryption
        T = permutation(T, Constants::IP); 

        T = encryption(T, key);
        
        T = permutation(T, Constants::IP_reverse);
        /////////////////

        for (int j = 0; j < 8; ++j)
            dataEnc.push_back(T[j]);
    }
    return dataEnc;
}

std::vector<char> decrypt(std::vector<char>& data, std::array<char, 8> key)
{
    size_t dSize = data.size();

    if (dSize == 0 || dSize % 8 != 0)
        return std::vector<char>();

    std::vector<char> dataDec;
    std::array<char, 8> T;
    
    for (int i = 0; i < dSize / 8; ++i)
    {
        T = {};
        for (int j = 0; j < 8; ++j)
        {
            //if (i * 8 + j < dSize)
            T[j] = data[i * 8 + j];
            //else
            //    T[j] = 0;
        }

        // DES-ECB decryption
        //T = permutation(T, Constants::IP_reverse); 
        T = permutation(T, Constants::IP); 

        T = decryption(T, key);
        
        //T = permutation(T, Constants::IP);
        T = permutation(T, Constants::IP_reverse); 
        /////////////////

        for (int j = 0; j < 8; ++j)
            dataDec.push_back(T[j]);
    }
    return dataDec;
}

int getRandomNumber(int min, int max)
{   // Вихрь Мерсенна
    std::random_device rd;
    std::mt19937 getRand(rd());

    double fraction = 1.0 / (static_cast<double>(getRand.max()) + 1.0);

    return static_cast<int>(getRand() * fraction * (max - min + 1) + min); 
}

std::array<char, 7> genKey()
{
    std::array<char, 7> key{};
    for (int i = 0; i < 7; ++i)
    {
        key[i] |= getRandomNumber(0x0, 0xFF);
    }
    return key;
}

std::array<char, 8> expandKey(std::array<char, 7> key)
{
    std::array<char, 8> eKey{};
    int keyByte = 0;
    int keyBit = 0;
    int ones = 0;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (keyBit == 8)
            {
                ++keyByte;
                keyBit = 0;
            }

            if (j < 7)
            {
                unsigned char bit = (key[keyByte] << keyBit++) & 0x80;
                if (bit != 0)
                {
                    ++ones;
                    eKey[i] |= bit >> j;
                }
            } else
            {
                if (ones % 2 == 0)
                    eKey[i] |= 0x1;
                ones = 0;
            }
        }
    }
    return eKey;
}

std::array<char, 7> extractKey(std::array<char, 8> eKey)
{
    std::array<char, 7> key{};
    int eKeyByte = 0;
    int eKeyBit = 0;
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (eKeyBit == 7)
            {
                ++eKeyByte;
                eKeyBit = 0;
            }

            key[i] |= (((eKey[eKeyByte] << (eKeyBit++)) & 0x80) >> j);
        }
    }
    return key;
}

} // DES_functions


/*
std::array<char, 8> expandKey(std::array<char, 7> key)
{
    std::array<char, 8> eKey{};
    int keyByte = 0;
    int keyBit = 0;
    int ones = 0;

    int eKeyByte = 0;
    int eKeyBit = 0;

    keyBit = 0;
    keyByte = 0;

    for (int i = 0; i < 64; ++i)
    {
        eKeyByte = i / 8;
        eKeyBit = i % 8;

        if (keyBit == 8)
        {
            ++keyByte;
            keyBit = 0;
        }

        if ((i + 1) % 8 != 0)
        {
            unsigned char bit = (key[keyByte] << keyBit++) & 0x80;
            if (bit != 0)
                ++ones;
            eKey[eKeyByte] |= bit >> eKeyBit;
        } else
        {
            if (ones % 2 == 0)
                eKey[i] |= 0x1;
            ones = 0;
        }
    }

    return eKey;
}
*/