#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

namespace functions
{
    int getRandomNumber(int min, int max);

    inline bool isCoprime65537(int a);

    inline bool isCoprime3(int a);

    bool isPrime(int n);

    int genRand();

    struct touple
    {
        int d1;
        int d2;
    };

    touple findD(int a, int b);

    int inverse(int a, int n);

    int pow(int a, unsigned int b);

    int modpow(int base, int exp, int mod);
}

#endif // __FUNCTIONS_H__