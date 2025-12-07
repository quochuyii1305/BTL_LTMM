#include "dsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>

void DSA_sign(const mpz_t message_hash, const mpz_t p, const mpz_t q, 
              const mpz_t g, const mpz_t x, mpz_t r, mpz_t s) {
    gmp_randstate_t state;
    gmp_randinit_default(state);
    unsigned long seed = (unsigned long) time(NULL) ^ (unsigned long) clock();
    gmp_randseed_ui(state, seed);
    
    mpz_t k, k_inv, temp1, temp2;
    mpz_inits(k, k_inv, temp1, temp2, NULL);
    
    // Generate random k in range [1, q-1]
    do {
        mpz_urandomm(k, state, q);
    } while (mpz_cmp_ui(k, 0) == 0);
    
    // r = (g^k mod p) mod q
    mpz_powm(temp1, g, k, p);
    mpz_mod(r, temp1, q);
    
    // k_inv = k^(-1) mod q
    if (mpz_invert(k_inv, k, q) == 0) {
        mpz_set_ui(s, 0);
        mpz_set_ui(r, 0);
        mpz_clears(k, k_inv, temp1, temp2, NULL);
        gmp_randclear(state);
        return;
    }
    
    // s = k_inv * (message_hash + x * r) mod q
    mpz_mul(temp1, x, r);
    mpz_add(temp2, message_hash, temp1);
    mpz_mul(temp1, k_inv, temp2);
    mpz_mod(s, temp1, q);
    
    mpz_clears(k, k_inv, temp1, temp2, NULL);
    gmp_randclear(state);
    
    printf("DSA Signature Generated:\n");
}

bool DSA_verify(const mpz_t message_hash, const mpz_t r, const mpz_t s,
                const mpz_t p, const mpz_t q, const mpz_t g, const mpz_t y) {
    if (mpz_cmp_ui(r, 0) <= 0 || mpz_cmp(r, q) >= 0 || 
        mpz_cmp_ui(s, 0) <= 0 || mpz_cmp(s, q) >= 0) {
        printf("DSA Signature Verification Result: Invalid (bounds)\n");
        return false;
    }
    
    mpz_t w, u1, u2, v, temp1, temp2;
    mpz_inits(w, u1, u2, v, temp1, temp2, NULL);
    
    // w = s^(-1) mod q
    if (mpz_invert(w, s, q) == 0) {
        mpz_clears(w, u1, u2, v, temp1, temp2, NULL);
        printf("DSA Signature Verification Result: Invalid (no inverse)\n");
        return false;
    }
    
    // u1 = (message_hash * w) mod q
    mpz_mul(temp1, message_hash, w);
    mpz_mod(u1, temp1, q);
    
    // u2 = (r * w) mod q
    mpz_mul(temp1, r, w);
    mpz_mod(u2, temp1, q);
    
    // v = ((g^u1 * y^u2) mod p) mod q
    mpz_powm(temp1, g, u1, p);
    mpz_powm(temp2, y, u2, p);
    mpz_mul(temp1, temp1, temp2);
    mpz_mod(temp1, temp1, p);
    mpz_mod(v, temp1, q);
    
    bool is_valid = (mpz_cmp(v, r) == 0);
    
    mpz_clears(w, u1, u2, v, temp1, temp2, NULL);
    
    printf("DSA Signature Verification Result: %s\n", is_valid ? "Valid" : "Invalid");
    return is_valid;
}