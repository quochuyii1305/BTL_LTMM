#ifndef PRIME_H
#define PRIME_H

#include <gmp.h>

// Kiểm tra số nguyên tố
int isProbablePrime(mpz_t n, int iterations);

// Tìm số nguyên tố tiếp theo
void getNextPrime(mpz_t result, const char* start);

// Tìm ước số nguyên tố của n
void findQ(mpz_t result, mpz_t n);

// Sinh tham số DSA chuẩn (p và q)
void generateDSAParams(mpz_t p, mpz_t q, unsigned int L, unsigned int N, gmp_randstate_t state);

#endif