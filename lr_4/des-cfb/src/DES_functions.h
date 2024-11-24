#ifndef DES_FUNCTIONS_H
#define DES_FUNCTIONS_H

#include <iostream>
#include <array>
#include <vector>

namespace DES_functions
{

    std::array<char, 8> initialPermutation(std::array<char, 8> T);

    std::ostream& printBinary(std::ostream& out, char letter);


    std::array<char, 8> permutation(std::array<char, 8> T, std::array<int, 64> IP); // !

    std::array<char, 8> encryption(std::array<char, 8> TP, std::array<char, 8> key);

        std::array<char, 7> prepareKey(std::array<char, 8> key); // !

        std::array<char, 7> shiftCD(std::array<char, 7> CD, int shift); // !

        std::array<char, 6> getK(std::array<char, 7> CDS); // !

        std::array<char, 4> getL(std::array<char, 8> T); // !

        std::array<char, 4> getR(std::array<char, 8> T); // !

        std::array<char, 4> f(std::array<char, 4> RorL, std::array<char, 6> K); // !

            std::array<char, 6> expand(std::array<char, 4> RorL); // !

            std::array<char, 6> xor48(std::array<char, 6> RorLE, std::array<char, 6> K); // !

            std::array<char, 8> getB(std::array<char, 6> RorLEK); // !

            std::array<char, 4> shrink(std::array<char, 8> B); // !

            std::array<char, 4> transposition(std::array<char, 4> BS); // !
        
        std::array<char, 8> combineLR(std::array<char, 4> L, std::array<char, 4> R); // !

    std::array<char, 8> decryption(std::array<char, 8> revTP, std::array<char, 8> K);

        std::array<char, 7> reverseShiftCD(std::array<char, 7> CD, int shift); // !

    std::vector<char> encrypt(std::vector<char>& data, std::array<char, 8> key);

    std::vector<char> decrypt(std::vector<char>& data, std::array<char, 8> key);
    

    int getRandomNumber(int min, int max);

    std::array<char, 7> genKey();

    std::array<char, 8> expandKey(std::array<char, 7> key);

    std::array<char, 7> extractKey(std::array<char, 8> key);

}

#endif // DES_FUNCTIONS_H