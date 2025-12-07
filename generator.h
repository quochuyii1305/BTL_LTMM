#ifndef GENERATOR_H
#define GENERATOR_H

#include <gmp.h>

// Sinh generator g
void getGen(mpz_t result, mpz_t p, mpz_t q, gmp_randstate_t state);

#endif // GENERATOR_H