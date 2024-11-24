#include "functions.h"

#include <iostream>
#include <random> // C++11, std::random_device, std::mt19937 
#include <numeric> // std::gcd std::lcm
#include <cstdlib> // std::abs

int functions::getRandomNumber(int min, int max)
{   // Вихрь Мерсенна
    std::random_device rd;
    std::mt19937 getRand(rd());

    double fraction = 1.0 / (static_cast<double>(getRand.max()) + 1.0);

    return static_cast<int>(getRand() * fraction * (max - min + 1) + min); 
}

inline bool functions::isCoprime65537(int a)
{
    return ((a / 65537) == 0 ? false : true); 
}

inline bool functions::isCoprime3(int a)
{
    return ((a % 3) == 0 ? false : true); 
}

bool functions::isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }

    return true;
}

int functions::genRand()
{
    int a = getRandomNumber(10, 40);
    while (!isCoprime3(a - 1) || !isPrime(a))
    {
        a = getRandomNumber(10, 40);
    }
    return a;
}

functions::touple functions::findD(int a, int b)
{

    int old_r = a;
    int r = b;
    int old_s = 1;
    int s = 0;
    int old_t = 0;
    int t = 1;
    int q;
    int prov;
    while (r != 0)
    {
        q = old_r / r;

        prov = r;
        r = old_r - q * prov;
        old_r = prov;

        prov = s;
        s = old_s - q * prov;
        old_s = prov;

        prov = t;
        t = old_t - q * prov;
        old_t = prov;
    }
    std::cout << "old_s (d1) = " << old_s << ", old_t (d2) = " << old_t << '\n';
    //int d = (std::abs(old_s) > std::abs(old_t) ? std::abs(old_s) : std::abs(old_t));
    touple d;
    d.d1 = old_s;
    d.d2 = old_t;

    //int d = ((x >= 0) ? x : -x);
    return d;
}

int functions::inverse(int a, int n)
{
    int t = 0; int newt = 1;
    int r = n; int newr = a;
    int q, prov;
    while (newr != 0)
    {
        q = r / newr;

        prov = newt;
        newt = t - q * prov;
        t = prov;

        prov = newr;
        newr = r - q * prov;
        r = prov;
    }
    if (r > 1)
        throw ("non inversable");
    if (t < 0)
        t = t + n;
    return t;
}

int functions::pow(int a, unsigned int b)
{
    int result = 1;
    if (b == 0)
        return 1; 
    for (int i = 0; i < b; ++i)
        result *= a;
    return result;
}

int functions::modpow(int base, int exp, int mod)
{
    if (mod == 1)
        return 0;
    int c = 1;
    for (int e_prime = 0; e_prime < exp; ++e_prime)
    {
        c = (c * base) % mod;
    }
    return c;
}

/*
    int findD(int Ln, int e)
    {
    int a = Ln;
    int b = e;
    int q, r;
    int x1 = 0, x2 = 1, y1 = 1, y2 = 0;
    while (b > 0)
    {
        q = a / b;
        r = a - q * b;
        int x = x2 - q * x1;
        int y = y2 - q * y1;
        a = b;
        b = r;
        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
    }
    int x = (x2 > y2 ? y2 : x2);
    int d = Ln - (x >= 0 ? x : -x);
    return d;
    }
    */