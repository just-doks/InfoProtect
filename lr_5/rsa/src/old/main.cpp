#include <iostream>
#include <numeric> // std::gcd std::lcm
#include <limits>
#include <cstdlib> // std::abs
#include <string>
#include <sstream>

#include "gmp.h"

//#include "bigint.h"

#include "functions.h"

#include <random> // C++11, std::random_device, std::mt19937 

uint64_t getRandomNumber(uint64_t min, uint64_t max)
{   // Вихрь Мерсенна
    std::random_device rd;
    //std::mt19937 getRand(rd());
    std::mt19937_64 getRand(rd());

    long double fraction = 1.0 / (static_cast<long double>(getRand.max()) + 1.0);

    return static_cast<uint64_t>(getRand() * fraction * (max - min + 1) + min); 
}

std::string genNumStr(size_t length)
{
    char ch;
    std::string str;
    str += getRandomNumber(1, 9) + '0';
    for (int i = 1; i < length; ++i)
        str += getRandomNumber(0, 9) + '0';
    return str;
}

void 
makeprime (mpz_ptr rand, int bits, int e)
{
    // *********************** VARIABLE DECLARATION *********************** //
    // initilize the variables as gmp class instances
    mpz_t l, m, h, temp;
    unsigned long seed = getRandomNumber(0x800000, std::numeric_limits<uint64_t>::max());
    // perform inits to create variable pointers with 0 value
    mpz_inits(l, m, h, temp, NULL);
    //mpz_init(rand);

    //int bits = 128;

    // calculate the random number floor
    mpz_ui_pow_ui(l, 2, bits - 1);

    // calculate the random number middle point
    mpz_ui_pow_ui(m, 2, bits - 2);

    // add middle point to low boundary
    mpz_add(l, l, m);
    //gmp_printf("prime number low boundary: %Zd\n", l);

    // calculate the random number roof
    mpz_ui_pow_ui(h, 2, bits);
    //gmp_printf("prime number high boundary: %Zd\n", h);

    // initilze the state object for the random generator functions
    gmp_randstate_t rstate;
    // initialize state for a Mersenne Twister algorithm. This algorithm is fast and has good randomness properties.
    gmp_randinit_mt(rstate);

    // create the generator seed for the random engine to reference 
    gmp_randseed_ui(rstate, seed);

    /*
    Function:
    int mpz_probab_prime_p (const mpz_t n, int reps)

    Determine whether n is prime. Return 2 if n is definitely prime, return 1 if n is probably prime (without being certain), 
    or return 0 if n is definitely composite.
    */
    do {
        //seed = getRandomNumber(0x800000, std::numeric_limits<uint64_t>::max());
        //gmp_randseed_ui(rstate, seed);

        // return a uniformly distributed random number in the range 0 to 2^N - 1, inclusive.
        mpz_urandomb(rand, rstate, bits - 1);

        //mpz_rrandomb(rand, rstate, 32);
        

        // add the random number to the low number, which will make sure the random number is between the low and high ranges
        mpz_add(rand, rand, l);

        mpz_nextprime(rand, rand);

        //gmp_printf("randomly generated prime number: %Zd\n", rand);

        mpz_sub_ui(temp, rand, 1);

    } while (!(mpz_probab_prime_p(rand, 50)) 
            || mpz_gcd_ui(NULL, temp, e) != 1 
            || mpz_cmp(rand, h) > 0);        

    // *********************** GARBAGE COLLECTION *********************** //
    // empty the memory location for the random generator state
    gmp_randclear(rstate);
    // clear the memory locations for the variables used to avoid leaks
    mpz_clears(l, m, h, temp, NULL);
    // mpz_clear(rand);
}

int main (int argc, char* argv[])
{
    namespace fn = functions;

    int p;
    int q;
    do
    {
        p = fn::genRand();
        q = fn::genRand();
    } while (p == q);
    std::cout << "p = " << p << ", q = " << q << '\n';

    int n = p * q;
    std::cout << "n = " << n << '\n';

    int Ln = std::lcm(p - 1, q - 1);
    std::cout << "Ln = " << Ln << '\n';
    
    int e = 3;
    if (std::gcd(Ln, e) == 1)
        std::cout << "gcd == 1\n";

    // std::cout << "1 mod Ln = " << 1 % Ln << '\n';

    int d;
    try
    {
        d = fn::inverse(e, Ln);/* code */
    }
    catch(char* e)
    {
        std::cerr << e << '\n';
        exit(0);
    }
    std::cout << "d = " << d << '\n';

    int m = 12;
    std::cout << "data: " << m << '\n';

    int c = fn::pow(m, 3) % n;
    std::cout << "encrypted data: " << c << '\n';

    int dm = fn::modpow(c, d, n);
    std::cout << "decrypted data (d): " << dm <<'\n';

    mpz_t P, Q;
    mpz_inits(P, Q, NULL);


    mpz_t tenPowTen, temp;
    mpz_init(tenPowTen);
    mpz_init(temp);
    //std::string sTen = "1";
    //for (int i = 0; i < 10; ++i)
    //    sTen += '0';

    //mpz_init_set_str(tenPowTen, sTen.c_str(), 10);
    mpz_ui_pow_ui(tenPowTen, 10, 10);
    gmp_printf("ten power ten is %Zd\n", tenPowTen);


    if (true)
    {
        e = 65537;
        do {
            makeprime(P, 512, e);
            makeprime(Q, 512, e);
            if (mpz_cmp(P, Q))
                mpz_sub(temp, P, Q);
            else
                mpz_sub(temp, Q, P);
            //mpz_abs(temp, temp);
        } while (mpz_cmp(temp, tenPowTen) <= 0);
    } else
    {
        mpz_set_ui(P, p);
        mpz_set_ui(Q, q);
    }

    

    //gmp_printf("P is %Zd\n", P);
    //gmp_printf("Q is %Zd\n", Q);

    mpz_t N, LN, Pprev, Qprev;
    mpz_inits(N, LN, Pprev, Qprev, NULL);

    mpz_mul(N, P, Q);
    mpz_sub_ui(Pprev, P, 1);
    mpz_sub_ui(Qprev, Q, 1);
    mpz_lcm(LN, Pprev, Qprev);
    if (mpz_gcd_ui(NULL, LN, e) == 1)
        std::cout << "gcd(LN, e) == 1\n";


    mpz_t D, E, M, ENC, DEC;
    mpz_init_set_ui(E, e);
    mpz_inits(D, ENC, DEC, NULL);


    mpz_invert(D, E, LN);

    mpz_init_set_ui(M, m);

    mpz_powm(ENC, M, E, N);

    mpz_powm(DEC, ENC, D, N);
    
    gmp_printf("decrypted data: %Zd\n", DEC);

    //std::cout << "encrypted data: " << ENC << '\n';


    std::cout << "size in base: " << mpz_sizeinbase(ENC, 2) << '\n';

    std::cout << "decrypted data (cout): " << DEC << '\n';

    mpz_clear(tenPowTen);
    mpz_clears(P, Q, temp, NULL);
    mpz_clears(N, LN, Pprev, Qprev, NULL);
    mpz_clears(D, E, M, ENC, DEC, NULL);
    
    
    return 0;
}