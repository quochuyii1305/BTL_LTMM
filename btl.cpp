#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gmp.h>
#include <gmpxx.h>

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

int main() {
    // Khởi tạo random state
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
    
    // Khai báo biến
    mpz_t p, q, g, x, y, k, r, hashVal, kInv, s;
    mpz_t w, u1, u2, v, temp1, temp2;
    
    mpz_inits(p, q, g, x, y, k, r, hashVal, kInv, s, NULL);
    mpz_inits(w, u1, u2, v, temp1, temp2, NULL);
    
    // Sinh các tham số công khai
    getNextPrime(p, "10600");
    mpz_sub_ui(temp1, p, 1);
    findQ(q, temp1);
    getGen(g, p, q, state);
    
    printf("\nSimulation of Digital Signature Algorithm\n");
    printf("\nGlobal public key components are:\n");
    gmp_printf("\nP is: %Zd\n", p);
    gmp_printf("\nQ is: %Zd\n", q);
    gmp_printf("\nG is: %Zd\n", g);
    
    // Sinh khóa riêng x
    mpz_urandomm(x, state, q);
    
    // Tính khóa công khai y = g^x mod p
    mpz_powm(y, g, x, p);
    
    // Sinh k ngẫu nhiên
    mpz_urandomm(k, state, q);
    
    // Tính r = (g^k mod p) mod q
    mpz_powm(temp1, g, k, p);
    mpz_mod(r, temp1, q);
    
    // Sinh hash giả lập
    mpz_urandomb(hashVal, state, mpz_sizeinbase(p, 2));
    
    // Tính s = k^(-1) * (H + x*r) mod q
    mpz_invert(kInv, k, q);
    mpz_mul(temp1, x, r);
    mpz_add(temp2, hashVal, temp1);
    mpz_mul(s, kInv, temp2);
    mpz_mod(s, s, q);
    
    printf("\nSecret information:\n");
    gmp_printf("X (private) is: %Zd\n", x);
    gmp_printf("K (secret) is: %Zd\n", k);
    gmp_printf("Y (public) is: %Zd\n", y);
    gmp_printf("H (mdhash) is: %Zd\n", hashVal);
    
    printf("\nGenerating digital signature:\n");
    gmp_printf("R is: %Zd\n", r);
    gmp_printf("S is: %Zd\n", s);
    
    // Xác thực chữ ký
    // w = s^(-1) mod q
    mpz_invert(w, s, q);
    
    // u1 = H * w mod q
    mpz_mul(temp1, hashVal, w);
    mpz_mod(u1, temp1, q);
    
    // u2 = r * w mod q
    mpz_mul(temp1, r, w);
    mpz_mod(u2, temp1, q);
    
    // v = (g^u1 * y^u2 mod p) mod q
    mpz_powm(temp1, g, u1, p);
    mpz_powm(temp2, y, u2, p);
    mpz_mul(v, temp1, temp2);
    mpz_mod(v, v, p);
    mpz_mod(v, v, q);
    
    printf("\nVerifying digital signature (checkpoints):\n");
    gmp_printf("W is: %Zd\n", w);
    gmp_printf("U1 is: %Zd\n", u1);
    gmp_printf("U2 is: %Zd\n", u2);
    gmp_printf("V is: %Zd\n", v);
    
    // So sánh v và r
    if (mpz_cmp(v, r) == 0) {
        gmp_printf("\nSuccess: Digital signature is verified!\n%Zd\n", r);
    } else {
        printf("\nError: Incorrect digital signature\n");
    }
    
    // Giải phóng bộ nhớ
    mpz_clears(p, q, g, x, y, k, r, hashVal, kInv, s, NULL);
    mpz_clears(w, u1, u2, v, temp1, temp2, NULL);
    gmp_randclear(state);
    
    return 0;
}