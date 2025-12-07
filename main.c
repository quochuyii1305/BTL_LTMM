#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gmp.h>
#include "prime.h"
#include "generator.h"
#include "dsa.h"

int main() {
    // Khởi tạo random state
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
    
    // Khai báo biến
    mpz_t p, q, g, x, y, r, s, hashVal;
    mpz_t temp1, start_p;
    
    mpz_inits(p, q, g, x, y, r, s, hashVal, temp1, start_p, NULL);
    
    // Sinh các tham số công khai
    mpz_ui_pow_ui(start_p, 2, 511);
    char *str_p = mpz_get_str(NULL, 10, start_p);
    getNextPrime(p, str_p);
    free(str_p);
    
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
    
    // Sinh hash giả lập
    mpz_urandomb(hashVal, state, mpz_sizeinbase(p, 2));
    
    printf("\nSecret information:\n");
    gmp_printf("X (private) is: %Zd\n", x);
    gmp_printf("Y (public) is: %Zd\n", y);
    gmp_printf("H (mdhash) is: %Zd\n", hashVal);
    
    // Ký số
    printf("\nGenerating digital signature:\n");
    DSA_sign(hashVal, p, q, g, x, r, s);
    gmp_printf("R is: %Zd\n", r);
    gmp_printf("S is: %Zd\n", s);
    
    // Xác thực chữ ký
    printf("\nVerifying digital signature:\n");
    bool verified = DSA_verify(hashVal, r, s, p, q, g, y);
    
    if (verified) {
        gmp_printf("\nSuccess: Digital signature is verified!\n%Zd\n", r);
    } else {
        printf("\nError: Incorrect digital signature\n");
    }
    
    // Giải phóng bộ nhớ
    mpz_clears(p, q, g, x, y, r, s, hashVal, temp1, start_p, NULL);
    gmp_randclear(state);
    
    return 0;
}