#include "RSA.h"


RSA::Key::Key(const RSA::Key& key) : 
    exponent(key.exponent), 
    modulus(key.modulus) {}

RSA::Key::Key(const MPZ& exp, const MPZ& mod) :
    exponent(exp),
    modulus(mod) {}

RSA::Key& RSA::Key::operator=(const Key& key)
{
    exponent = key.exponent;
    modulus = key.modulus;
    return *this;
}

const MPZ& RSA::Key::exp() const
{
    return exponent;
}
MPZ& RSA::Key::exp()
{
    return exponent;
}
void RSA::Key::exp(const MPZ& exp)
{
    exponent = exp;
}

const MPZ& RSA::Key::mod() const
{
    return modulus;
}
MPZ& RSA::Key::mod()
{
    return modulus;
}
void RSA::Key::mod(const MPZ& mod)
{
    modulus = mod;
}