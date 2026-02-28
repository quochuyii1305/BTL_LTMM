#include "dsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gmp.h>
#include <iostream>

using namespace std;

void DSA_sign(const mpz_t message_hash, const mpz_t p, const mpz_t q, const mpz_t g, const mpz_t x, mpz_t r, mpz_t s) {
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
        // inverse doesn't exist; this is extremely unlikely if q is prime; retry
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

    cout << "DSA Signature Generated:" << endl;
}

bool DSA_verify(const mpz_t message_hash, const mpz_t r, const mpz_t s, const mpz_t p, const mpz_t q, const mpz_t g, const mpz_t y) {
    if (mpz_cmp_ui(r, 0) <= 0 || mpz_cmp(r, q) >= 0 || mpz_cmp_ui(s, 0) <= 0 || mpz_cmp(s, q) >= 0) {
        cout << "DSA Signature Verification Result: Invalid (bounds)" << endl;
        return false; // Invalid signature
    }

    mpz_t w, u1, u2, v, temp1, temp2;
    mpz_inits(w, u1, u2, v, temp1, temp2, NULL);

    // w = s^(-1) mod q
    if (mpz_invert(w, s, q) == 0) {
        mpz_clears(w, u1, u2, v, temp1, temp2, NULL);
        cout << "DSA Signature Verification Result: Invalid (no inverse)" << endl;
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

    cout << "DSA Signature Verification Result: " << (is_valid ? "Valid" : "Invalid") << endl;
    return is_valid;
}

int main() {
    mpz_t p, q, g, x, y, message_hash, r, s;
    mpz_inits(p, q, g, x, y, message_hash, r, s, NULL);

    // Generate DSA parameters: choose sizes
    const unsigned int q_bits = 160;   // size of q in bits (typical DSA parameter)
    const unsigned int p_bits = 512;   // size of p in bits for demo (use >=1024 for real use)

    // Initialize RNG
    gmp_randstate_t state;
    gmp_randinit_default(state);
    unsigned long seed = (unsigned long) time(NULL) ^ (unsigned long) clock();
    gmp_randseed_ui(state, seed);

    // 1) Generate prime q of q_bits
    mpz_t tmp_k;
    mpz_init(tmp_k);
    do {
        mpz_urandomb(q, state, q_bits);
        mpz_nextprime(q, q);
    } while (mpz_sizeinbase(q, 2) != q_bits && mpz_sizeinbase(q, 2) != q_bits - 1);

    // 2) Find p = k*q + 1 with p prime and p having p_bits bits
    mpz_t k, p_candidate;
    mpz_inits(k, p_candidate, NULL);
    bool found_p = false;
    unsigned int attempt = 0;
    while (!found_p && attempt < 1000) {
        // choose random k with appropriate size: p_bits - q_bits
        unsigned int k_bits = (p_bits > q_bits) ? (p_bits - q_bits) : 1;
        mpz_urandomb(k, state, k_bits);
        if (mpz_cmp_ui(k, 2) < 0) mpz_set_ui(k, 2);
        // p_candidate = k * q + 1
        mpz_mul(p_candidate, k, q);
        mpz_add_ui(p_candidate, p_candidate, 1);
        // check bit-size and primality
        if ((unsigned)mpz_sizeinbase(p_candidate, 2) == p_bits) {
            int is_prime = mpz_probab_prime_p(p_candidate, 25);
            if (is_prime > 0) {
                mpz_set(p, p_candidate);
                found_p = true;
                break;
            }
        }
        attempt++;
    }

    if (!found_p) {
        cout << "Failed to find p with desired properties after " << attempt << " attempts.\n";
        // fallback to small demo values
        mpz_set_ui(p, 23);
        mpz_set_ui(q, 11);
        mpz_set_ui(g, 2);
    } else {
        // 3) find generator g: pick h in [2, p-2] and compute g = h^{(p-1)/q} mod p, require g > 1
        mpz_t h, exp;
        mpz_inits(h, exp, NULL);
        mpz_sub_ui(tmp_k, p, 1);
        mpz_divexact(exp, tmp_k, q); // exp = (p-1)/q
        bool found_g = false;
        for (int i = 2; i < 1000 && !found_g; ++i) {
            mpz_set_ui(h, i);
            mpz_powm(g, h, exp, p);
            if (mpz_cmp_ui(g, 1) > 0) {
                found_g = true;
                break;
            }
        }
        mpz_clears(h, exp, NULL);
    }

    // private key x in [1, q-1]
    do {
        mpz_urandomm(x, state, q);
    } while (mpz_cmp_ui(x, 0) == 0);
    // public key y = g^x mod p
    mpz_powm(y, g, x, p);

    // message hash (choose random < q for demo)
    mpz_urandomm(message_hash, state, q);

    // Sign and verify
    DSA_sign(message_hash, p, q, g, x, r, s);

    bool valid = DSA_verify(message_hash, r, s, p, q, g, y);

    mpz_clears(tmp_k, k, p_candidate, NULL);
    gmp_randclear(state);

    mpz_clears(p, q, g, x, y, message_hash, r, s, NULL);
    return valid ? 0 : 1;
}