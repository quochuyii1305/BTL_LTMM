#include "prime.h"
#include <gmp.h>

// Kiểm tra số nguyên tố
int isProbablePrime(mpz_t n, int iterations) {
    return mpz_probab_prime_p(n, iterations);
}

// Tìm số nguyên tố tiếp theo
void getNextPrime(mpz_t result, const char* start) {
    mpz_set_str(result, start, 10);
    while (!isProbablePrime(result, 99)) {
        mpz_add_ui(result, result, 1);
    }
}

// Tìm ước số nguyên tố lớn nhất của n
void findQ(mpz_t result, mpz_t n) {
    mpz_t start, temp, zero;
    mpz_inits(start, temp, zero, NULL);
    
    mpz_set_ui(start, 2);
    mpz_set_ui(zero, 0);
    mpz_set(temp, n);
    
    while (!isProbablePrime(temp, 99)) {
        while (mpz_cmp_ui(temp, 0) != 0) {
            mpz_mod(result, temp, start);
            if (mpz_cmp(result, zero) == 0) {
                break;
            }
            mpz_add_ui(start, start, 1);
        }
        mpz_div(temp, temp, start);
    }
    
    mpz_set(result, temp);
    mpz_clears(start, temp, zero, NULL);
}