#include "MPZ.h"

//Assigning
MPZ& MPZ::operator=(const MPZ& OP)
{
    mpz_set(m_X, OP.m_X);
    return *this;
}
MPZ& MPZ::operator=(const unsigned long int OP)
{
    mpz_set_ui(m_X, OP);
    return *this;
}
MPZ& MPZ::operator=(const signed long int OP)
{
    mpz_set_si(m_X, OP);
    return *this;
}

MPZ& MPZ::operator+=(const MPZ& OP)
{
    mpz_add(m_X, m_X, OP.m_X);
    return *this;
}
MPZ& MPZ::operator+=(const unsigned long int OP)
{
    mpz_add_ui(m_X, m_X, OP);
    return *this;
}
MPZ& MPZ::operator-=(const MPZ& OP)
{
    mpz_sub(m_X, m_X, OP.m_X);
    return *this;
}
MPZ& MPZ::operator-=(const unsigned long int OP)
{
    mpz_sub_ui(m_X, m_X, OP);
    return *this;
}
MPZ& MPZ::operator*=(const MPZ& OP)
{
    mpz_mul(m_X, m_X, OP.m_X);
    return *this;
}
MPZ& MPZ::operator*=(const unsigned long int OP)
{
    mpz_mul_ui(m_X, m_X, OP);
    return *this;
}
MPZ& MPZ::operator/=(const MPZ& OP)
{
    mpz_cdiv_q(m_X, m_X, OP.m_X);
    return *this;
}
MPZ& MPZ::operator/=(const unsigned long int OP)
{
    mpz_cdiv_q_ui(m_X, m_X, OP);
    return *this;
}


// Comparison
bool MPZ::operator==(const MPZ& OP) const
{
    if (mpz_cmp(m_X, OP.m_X) == 0)
        return true;
    else
        return false;
}
bool MPZ::operator==(const unsigned long int OP) const
{
    if (mpz_cmp_ui(m_X, OP) == 0)
        return true;
    else
        return false;
}
bool MPZ::operator==(const long int OP) const
{
    if (mpz_cmp_si(m_X, OP) == 0)
        return true;
    else
        return false;
}
bool MPZ::operator==(const unsigned int OP) const
{
    if (mpz_cmp_ui(m_X, OP) == 0)
        return true;
    else
        return false;
}
bool MPZ::operator==(const int OP) const
{
    if (mpz_cmp_si(m_X, OP) == 0)
        return true;
    else
        return false;
}
//---
bool MPZ::operator!=(const MPZ& OP) const
{
    if (mpz_cmp(m_X, OP.m_X) != 0)
        return true;
    else
        return false;
}
bool MPZ::operator!=(const unsigned long int OP) const
{
    if (mpz_cmp_ui(m_X, OP) != 0)
        return true;
    else
        return false;
}
bool MPZ::operator!=(const signed long int OP) const
{
    if (mpz_cmp_si(m_X, OP) != 0)
        return true;
    else
        return false;
}
//---
bool MPZ::operator<(const MPZ& OP) const
{
    if (mpz_cmp(m_X, OP.m_X) < 0)
        return true;
    else
        return false;
}
bool MPZ::operator<(const unsigned long int OP) const
{
    if (mpz_cmp_ui(m_X, OP) < 0)
        return true;
    else
        return false;
}
bool MPZ::operator<(const signed long int OP) const
{
    if (mpz_cmp_si(m_X, OP) < 0)
        return true;
    else
        return false;
}
//---
bool MPZ::operator>(const MPZ& OP) const
{
    if (mpz_cmp(m_X, OP.m_X) > 0)
        return true;
    else
        return false;
}
bool MPZ::operator>(const unsigned long int OP) const
{
    if (mpz_cmp_ui(m_X, OP) > 0)
        return true;
    else
        return false;
}
bool MPZ::operator>(const signed long int OP) const
{
    if (mpz_cmp_si(m_X, OP) > 0)
        return true;
    else
        return false;
}
//---
bool MPZ::operator<=(const MPZ& OP) const
{
    if (mpz_cmp(m_X, OP.m_X) <= 0)
        return true;
    else
        return false;
}
bool MPZ::operator<=(const unsigned long int OP) const
{
    if (mpz_cmp_ui(m_X, OP) <= 0)
        return true;
    else
        return false;
}
bool MPZ::operator<=(const signed long int OP) const
{
    if (mpz_cmp_si(m_X, OP) <= 0)
        return true;
    else
        return false;
}
//---
bool MPZ::operator>=(const MPZ& OP) const
{
    if (mpz_cmp(m_X, OP.m_X) >= 0)
        return true;
    else
        return false;
}
bool MPZ::operator>=(const unsigned long int OP) const
{
    if (mpz_cmp_ui(m_X, OP) >= 0)
        return true;
    else
        return false;
}
bool MPZ::operator>=(const signed long int OP) const
{
    if (mpz_cmp_si(m_X, OP) >= 0)
        return true;
    else
        return false;
}
//---

// Increment Decrement
// prefix
MPZ& MPZ::operator++()
{
    mpz_add_ui(m_X, m_X, 1);
    return *this;
}
// postfix
MPZ MPZ::operator++(int)
{
    MPZ temp(*this);
    mpz_add_ui(m_X, m_X, 1);
    return temp;
}
// prefix
MPZ& MPZ::operator--()
{
    mpz_sub_ui(m_X, m_X, 1);
    return *this;
}
// postfix
MPZ MPZ::operator--(int)
{
    MPZ temp(*this);
    mpz_sub_ui(m_X, m_X, 1);
    return temp;
}

// Unary
MPZ MPZ::operator-() const
{
    MPZ temp(*this);
    mpz_neg(temp.m_X, temp.m_X);
    return temp;
}

// Add
MPZ MPZ::operator+(const MPZ& OP) const
{
    MPZ temp;
    mpz_add(temp.m_X, m_X, OP.m_X);
    return temp;
}
MPZ MPZ::operator+(const unsigned long int OP) const
{
    MPZ temp;
    mpz_add_ui(temp.m_X, m_X, OP);
    return temp;
}
MPZ operator+(const unsigned long int OP1, const MPZ& OP2)
{
    MPZ temp;
    mpz_add_ui(temp.m_X, OP2.m_X, OP1);
    return temp;
}
// Sub
MPZ MPZ::operator-(const MPZ& OP) const
{
    MPZ temp;
    mpz_sub(temp.m_X, m_X, OP.m_X);
    return temp;
}
MPZ MPZ::operator-(const unsigned long int OP) const
{
    MPZ temp;
    mpz_sub_ui(temp.m_X, m_X, OP);
    return temp;
}
MPZ operator-(const unsigned long int OP1, const MPZ& OP2)
{
    MPZ temp;
    mpz_ui_sub(temp.m_X, OP1, OP2.m_X);
    return temp;
}
// Mul
MPZ MPZ::operator*(const MPZ& OP) const
{
    MPZ temp;
    mpz_mul(temp.m_X, m_X, OP.m_X);
    return temp;
}
MPZ MPZ::operator*(const unsigned long int OP) const
{
    MPZ temp;
    mpz_mul_ui(temp.m_X, m_X, OP);
    return temp;
}
MPZ MPZ::operator*(const signed long int OP) const
{
    MPZ temp;
    mpz_mul_si(temp.m_X, m_X, OP);
    return temp;
}
MPZ operator*(const unsigned long int OP1, const MPZ& OP2)
{
    MPZ temp;
    mpz_mul_ui(temp.m_X, OP2.m_X, OP1);
    return temp;
}
MPZ operator*(const signed long int OP1, const MPZ& OP2)
{
    MPZ temp;
    mpz_mul_ui(temp.m_X, OP2.m_X, OP1);
    return temp;
}
// Div
MPZ MPZ::operator/(const MPZ& OP) const
{
    MPZ temp;
    mpz_cdiv_q(temp.m_X, m_X, OP.m_X);
    return temp;
}
MPZ MPZ::operator/(const unsigned long int OP) const
{
    MPZ temp;
    mpz_cdiv_q_ui(temp.m_X, m_X, OP);
    return temp;
}

// Exponentiation
MPZ& MPZ::pow(const MPZ& BASE, unsigned long int EXP)
{
    mpz_pow_ui(m_X, BASE.m_X, EXP);
    return *this;
}
MPZ& MPZ::pow(unsigned long int BASE, unsigned long int EXP)
{
    mpz_ui_pow_ui(m_X, BASE, EXP);
    return *this;
}
MPZ& MPZ::powm(const MPZ& BASE, const MPZ& EXP, const MPZ& MOD)
{
    mpz_powm(m_X, BASE.m_X, EXP.m_X, MOD.m_X);
    return *this;
}
MPZ& MPZ::powm(const MPZ& BASE, const unsigned long EXP, const MPZ& MOD)
{
    mpz_powm_ui(m_X, BASE.m_X, EXP, MOD.m_X);
    return *this;
}

// Number Theoretic Functions
MPZ MPZ::GCD(const MPZ& OP1, const MPZ& OP2)
{
    MPZ G;
    mpz_gcd(G.m_X, OP1.m_X, OP2.m_X);
    return G;
}
unsigned long MPZ::GCD(const MPZ& OP1, const unsigned long OP2)
{
    return mpz_gcd_ui(NULL, OP1.m_X, OP2);
}
MPZ MPZ::LCM(const MPZ& OP1, const MPZ& OP2)
{
    MPZ LCM;
    mpz_lcm(LCM.m_X, OP1.m_X, OP2.m_X);
    return LCM;
}
MPZ MPZ::LCM(const MPZ& OP1, const unsigned long OP2)
{
    MPZ LCM;
    mpz_lcm_ui(LCM.m_X, OP1.m_X, OP2);
    return LCM;
}
int MPZ::probably_prime(int REPS) const
{
    return mpz_probab_prime_p(m_X, REPS);
}
int MPZ::invert(const MPZ& OP1, const MPZ& OP2)
{
    return mpz_invert(m_X, OP1.m_X, OP2.m_X);
}

// Standard output
std::ostream& operator<<(std::ostream& out, const MPZ& OP)
{
    out << OP.m_X;
    return out;
}

// Getters
std::string MPZ::get_string(int BASE) const
{
    return std::string(mpz_get_str(NULL, BASE, m_X));
}

size_t MPZ::get_sizeInBase(int BASE) const
{
    return mpz_sizeinbase(m_X, BASE);
}

//Import - Export
MPZ& MPZ::importData(size_t COUNT, int ORDER, size_t SIZE, int ENDIAN, size_t NAILS, const void* OP)
{
    mpz_import(m_X, COUNT, ORDER, SIZE, ENDIAN, NAILS, OP);
    return *this;
}
void* MPZ::exportData(void *ROP, size_t *COUNTP, int ORDER, size_t SIZE, int ENDIAN, size_t NAILS)
{
    return mpz_export(ROP, COUNTP, ORDER, SIZE, ENDIAN, NAILS, m_X);
}

// Setters
// Number Theoretic Functions
MPZ& MPZ::set_nextPrime()
{
    mpz_nextprime(m_X, m_X);
    return *this;
}
MPZ& MPZ::set_GCD(const MPZ& OP1, const MPZ& OP2)
{
    mpz_gcd(m_X, OP1.m_X, OP2.m_X);
    return *this;
}
MPZ& MPZ::set_GCD(const MPZ& OP1, const unsigned long int OP2)
{
    mpz_gcd_ui(m_X, OP1.m_X, OP2);
    return *this;
}
MPZ& MPZ::set_LCM(const MPZ& OP1, const MPZ& OP2)
{
    mpz_lcm(m_X, OP1.m_X, OP2.m_X);
    return *this;
}
MPZ& MPZ::set_LCM(const MPZ& OP1, const unsigned long int OP2)
{
    mpz_lcm_ui(m_X, OP1.m_X, OP2);
    return *this;
}
// Assign string
MPZ& MPZ::set_str(const char* STR, int BASE)
{
    mpz_set_str(m_X, STR, BASE);
    return *this;
}
MPZ& MPZ::set_str(std::string STR, int BASE)
{
    mpz_set_str(m_X, STR.c_str(), BASE);
    return *this;
}
// Random Number Functions
MPZ& MPZ::set_urandomb(RandState& rstate, unsigned long int N)
{
    mpz_urandomb(m_X, rstate.m_rstate, N);
    return *this;
}
MPZ& MPZ::set_urandomm(RandState& rstate, const MPZ& N)
{
    mpz_urandomm(m_X, rstate.m_rstate, N.m_X);
    return *this;
}
MPZ& MPZ::set_rrandomb(RandState& rstate, unsigned long int N)
{
    mpz_rrandomb(m_X, rstate.m_rstate, N);
    return *this;
}