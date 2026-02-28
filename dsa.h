#ifndef DSA_H
#define DSA_H

#include <gmp.h>

void DSA_sign(const mpz_t message_hash, const mpz_t p, const mpz_t q, const mpz_t g, const mpz_t x, mpz_t r, mpz_t s);
bool DSA_verify(const mpz_t message_hash, const mpz_t r, const mpz_t s, const mpz_t p, const mpz_t q, const mpz_t g, const mpz_t y);

#endif