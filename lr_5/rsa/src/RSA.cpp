#include "RSA.h"
#include <limits>
#include <cstdint> // int8_t, uint8_t, int16_t, int32_t, int64_t
#include <random> // C++11, std::random_device, std::mt19937 

uint64_t RSA::getRandomNumber(uint64_t min, uint64_t max)
{   // Вихрь Мерсенна
    std::random_device rd;
    std::mt19937_64 getRand(rd());

    long double fraction = 1.0 / (static_cast<long double>(getRand.max()) + 1.0);

    return static_cast<uint64_t>(getRand() * fraction * (max - min + 1) + min); 
}

MPZ RSA::makeprime(int bits, unsigned long exp)
{
    MPZ rand;
    // initilize the variables as gmp class instances
    MPZ l, m, h;

    // calculate the random number floor
    l.pow(2, bits - 1);

    // calculate the random number middle point
    m.pow(2, bits - 2);

    // add middle point to low boundary
    l += m;

    // calculate the random number roof
    h.pow(2, bits);

    // initilze the state object for the random generator functions
    // initialize state for a Mersenne Twister algorithm. This algorithm is fast and has good randomness properties.
    RandState rstate;

    unsigned long seed = getRandomNumber(0x800000, std::numeric_limits<uint64_t>::max());

    // create the generator seed for the random engine to reference 
    rstate.seed(seed);

    do {
        //seed = getRandomNumber(0x800000, std::numeric_limits<uint64_t>::max());
        //rstate.seed(seed);

        // return a uniformly distributed random number in the range 0 to 2^N - 1, inclusive.
        rand.set_urandomb(rstate, bits - 1);

        // add the random number to the low number, which will make sure the random number is between the low and high ranges
        rand += l;

        // set random number to the next prime
        rand.set_nextPrime();

    } while (!rand.probably_prime(50) 
            || MPZ::GCD(rand - 1UL, exp) != 1 
            || (rand > h));        
    return rand;
}

bool RSA::genKeys(int bits, unsigned long exp)
{
    MPZ P, Q;
    do
    {
        P = makeprime(bits / 2, exp);
        Q = makeprime(bits / 2, exp);
    } while (P == Q);
    m_N = P * Q;

    MPZ LN;
    LN.set_LCM(P - 1, Q - 1);

    m_E = exp;

    if (!m_D.invert(m_E, LN))
        return false;
    return true;
}

RSA::Key RSA::getPublicKey()
{
    if (m_N == 0 || m_E == 0)
        throw(RSA_Exception("Error getting pub key: exp and mod don't set"));
    return Key(m_E, m_N);
}

RSA::Key RSA::getPrivateKey()
{
    if (m_N == 0 || m_D == 0)
        throw(RSA_Exception("Error getting priv key: exp and mod don't set"));
    return Key(m_D, m_N);
}

RSA::Key RSA::pub()
{
    return getPublicKey();
}

RSA::Key RSA::priv()
{
    return getPrivateKey();
}

#define MODULAR_EXPONENTIATION(INDATA, KEY) \
    size_t dSize = INDATA.size(); \
    size_t keyModSize = key.mod().get_sizeInBase(2); \
    if (keyModSize % 8 > 0) \
        keyModSize = keyModSize / 8 + 1; \
    else \
        keyModSize = keyModSize / 8; \
 \
    if (dSize > keyModSize) \
        throw RSA_Exception("Data is too big"); \
 \
    MPZ DATA; \
    DATA.importData(dSize, 1, sizeof(char), 0, 0, INDATA.data()); \
 \
    if (DATA > key.mod()) \
        throw RSA_Exception("Data is too big"); \
 \
    /* Encryption - Decryption */ \
    DATA.powm(DATA, key.exp(), key.mod()); \
 \
    char* buf; \
    size_t bsize; \
    buf = reinterpret_cast<char*>(DATA.exportData(NULL, &bsize, 1, sizeof(char), 0, 0)); \
 \
    std::vector<char> outData(buf, buf + bsize); \
 \
    return outData; \


std::vector<char> RSA::encrypt(const std::vector<char>& inData, const RSA::Key& key)
{
    MODULAR_EXPONENTIATION(inData, key)
}

std::vector<char> RSA::decrypt(const std::vector<char>& inData, const RSA::Key& key)
{
    MODULAR_EXPONENTIATION(inData, key)
}