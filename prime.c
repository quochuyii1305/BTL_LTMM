#include "prime.h"
#include <gmp.h>

// Kiểm tra số nguyên tố
int isProbablePrime(mpz_t n, int iterations) {
    return mpz_probab_prime_p(n, iterations);
}

// Tìm số nguyên tố tiếp theo
void getNextPrime(mpz_t result, const char* start) {
    mpz_nextprime(result, start);
}

// Sinh q và p theo chuẩn DSA
void generateDSAParams(mpz_t p, mpz_t q, unsigned int L, unsigned int N, gmp_randstate_t state) {
    mpz_t temp, p_minus_1, multiplier;
    mpz_inits(temp, p_minus_1, multiplier, NULL);
    
    mpz_urandomb(q, state, N);
    mpz_setbit(q, N-1);  
    mpz_nextprime(q, q);
    
    mpz_ui_pow_ui(temp, 2, L-1);
    mpz_div(multiplier, temp, q);  
    
    if (mpz_odd_p(multiplier)) {
        mpz_add_ui(multiplier, multiplier, 1);
    }
    
    int found = 0;
    while (!found) {
        mpz_mul(p, multiplier, q);
        mpz_add_ui(p, p, 1);
        
        if (mpz_sizeinbase(p, 2) == L && isProbablePrime(p, 50)) {
            found = 1;
        } else {
            mpz_add_ui(multiplier, multiplier, 2);
        }
    }
    
    mpz_clears(temp, p_minus_1, multiplier, NULL);
}


void findQ(mpz_t Q, mpz_t P) {
    mpz_t n, prime, temp;
    mpz_inits(n, prime, temp, NULL);

    mpz_sub_ui(n, P, 1);

    mpz_set_ui(prime, 2);
    mpz_set_ui(Q, 1);

    while (mpz_cmp_ui(n, 1) > 0) {

        if (is_probab_prime(n, 99)) {
            mpz_set(Q, n);
            break;
        }

        mpz_mod(temp, n, prime);
        if (mpz_cmp_ui(temp, 0) == 0) {
            mpz_set(Q, prime);
            mpz_divexact(n, n, prime);
        } else {
            gen_next_prime(prime, prime);
        }
    }

    mpz_clears(n, prime, temp, NULL);
}