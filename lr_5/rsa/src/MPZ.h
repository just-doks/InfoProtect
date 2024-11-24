#ifndef __MPZ_H__
#define __MPZ_H__

#include <iostream>
#include <string>
#include <cstdio> // FILE
#include "gmp.h"

class RandState;

class MPZ
{
    private:
        mpz_t m_X;
    public:
        MPZ() { mpz_init(m_X); }
        MPZ(const MPZ& X) { mpz_init_set(m_X, X.m_X); }
        MPZ(unsigned long int UI) { mpz_init_set_ui(m_X, UI); }
        ~MPZ() { mpz_clear(m_X); }

        // Assigning
        MPZ& operator=(const MPZ& OP);
        MPZ& operator=(const unsigned long int OP);
        MPZ& operator=(const signed long int OP);

        MPZ& operator+=(const MPZ& OP);
        MPZ& operator+=(const unsigned long int OP);
        MPZ& operator-=(const MPZ& OP);
        MPZ& operator-=(const unsigned long int OP);
        MPZ& operator*=(const MPZ& OP);
        MPZ& operator*=(const unsigned long int OP);
        MPZ& operator/=(const MPZ& OP);
        MPZ& operator/=(const unsigned long int OP);

        // Comparisons
        bool operator==(const MPZ& OP) const;
        bool operator==(const unsigned long int OP) const;
        bool operator==(const long int OP) const;
        bool operator==(const unsigned int OP) const;
        bool operator==(const int OP) const;
        bool operator!=(const MPZ& OP) const;
        bool operator!=(const unsigned long int OP) const;
        bool operator!=(const signed long int OP) const;
        bool operator<(const MPZ& OP) const;
        bool operator<(const unsigned long int OP) const;
        bool operator<(const signed long int OP) const;
        bool operator>(const MPZ& OP) const;
        bool operator>(const unsigned long int OP) const;
        bool operator>(const signed long int OP) const;
        bool operator<=(const MPZ& OP) const;
        bool operator<=(const unsigned long int OP) const;
        bool operator<=(const signed long int OP) const;
        bool operator>=(const MPZ& OP) const;
        bool operator>=(const unsigned long int OP) const;
        bool operator>=(const signed long int OP) const;

        // Increment Decrement
        MPZ& operator++(); // prefix
        MPZ operator++(int); // postfix
        MPZ& operator--(); // prefix
        MPZ operator--(int); // postfix

        // Unary
        MPZ operator-() const;

        // Add
        MPZ operator+(const MPZ& OP) const;
        MPZ operator+(const unsigned long int OP) const;
        friend MPZ operator+(const unsigned long int OP1, const MPZ& OP2);
        // Sub
        MPZ operator-(const MPZ& OP) const;
        MPZ operator-(const unsigned long int OP) const;
        friend MPZ operator-(const unsigned long int OP1, const MPZ& OP2);
        // Mul
        MPZ operator*(const MPZ& OP) const;
        MPZ operator*(const unsigned long int OP) const;
        MPZ operator*(const signed long int OP) const;
        friend MPZ operator*(const unsigned long int OP1, const MPZ& OP2);
        friend MPZ operator*(const signed long int OP1, const MPZ& OP2);
        // Div
        MPZ operator/(const MPZ& OP) const;
        MPZ operator/(const unsigned long int OP) const;

        // Exponentiation
        MPZ& pow(const MPZ& BASE, unsigned long int EXP);
        MPZ& pow(unsigned long int BASE, unsigned long int EXP);
        MPZ& powm(const MPZ& BASE, const MPZ& EXP, const MPZ& MOD);
        MPZ& powm(const MPZ& BASE, const unsigned long EXP, const MPZ& MOD);
        
        // Number Theoretic Functions
        static MPZ GCD(const MPZ& OP1, const MPZ& OP2);
        static unsigned long GCD(const MPZ& OP1, const unsigned long OP2);
        static MPZ LCM(const MPZ& OP1, const MPZ& OP2);
        static MPZ LCM(const MPZ& OP1, const unsigned long OP2);
        int probably_prime(int REPS) const; // 2 - definitely prime, 1 - probably, 0 - non-prime
        int invert(const MPZ& OP1, const MPZ& OP2);

        // Standard output
        friend std::ostream& operator<<(std::ostream& out, const MPZ& OP);

        // Getters
        // (-2) - (-36) upper case digits/ 2 - 36 lower case digits
        auto get_string(int BASE) const -> std::string;
        // 2 for bit length, 10 for digits length
        auto get_sizeInBase(int BASE) const -> size_t;

        // import and export
        MPZ& importData(size_t COUNT, int ORDER, size_t SIZE, int ENDIAN, size_t NAILS, const void* OP);
        void* exportData(void *ROP, size_t *COUNTP, int ORDER, size_t SIZE, int ENDIAN, size_t NAILS);

        // Setters
        // Number Theoretic Functions
        MPZ& set_nextPrime();
        MPZ& set_GCD(const MPZ& OP1, const MPZ& OP2);
        MPZ& set_GCD(const MPZ& OP1, const unsigned long int OP2);
        MPZ& set_LCM(const MPZ& OP1, const MPZ& OP2);
        MPZ& set_LCM(const MPZ& OP1, const unsigned long int OP2);
        // Assign string
        MPZ& set_str(const char* STR, int BASE = 0);
        MPZ& set_str(std::string STR, int BASE = 0);
        // Random Number Functions
        MPZ& set_urandomb(RandState& rstate, unsigned long int N); // from 0 to 2^N - 1
        MPZ& set_urandomm(RandState& rstate, const MPZ& N); // from 0 to N-1
        MPZ& set_rrandomb(RandState& rstate, unsigned long int N); // from 2^(N-1) to 2^N - 1

        friend class RandState;
};

class RandState
{
    private:
       gmp_randstate_t m_rstate;
    public:
        RandState() { gmp_randinit_mt(m_rstate); }
        ~RandState() { gmp_randclear(m_rstate); }

        void seed(const MPZ& SEED)
        {
            gmp_randseed(m_rstate, SEED.m_X);
        }
        void seed(unsigned long int SEED)
        {
            gmp_randseed_ui(m_rstate, SEED);
        }
        friend class MPZ;
};

#endif // __MPZ_H__