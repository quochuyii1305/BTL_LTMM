#include "generator.h"
#include <gmp.h>

// Sinh generator g
void getGen(mpz_t result, mpz_t p, mpz_t q, gmp_randstate_t state) {
    mpz_t h, exp, p_minus_1;
    mpz_inits(h, exp, p_minus_1, NULL);
    
    // Sinh số ngẫu nhiên h
    mpz_urandomm(h, state, p);
    
    // Tính exp = (p-1)/q
    mpz_sub_ui(p_minus_1, p, 1);
    mpz_div(exp, p_minus_1, q);
    
    // Tính g = h^exp mod p
    mpz_powm(result, h, exp, p);
    
    mpz_clears(h, exp, p_minus_1, NULL);
}