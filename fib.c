#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "C:\gmp\gmp.h"

const uint8_t tab32[32] = {
     0,  9,  1, 10, 13, 21,  2, 29,
    11, 14, 16, 18, 22, 25,  3, 30,
     8, 12, 20, 28, 15, 17, 24,  7,
    19, 27, 23,  6, 26,  5,  4, 31};

uint32_t log2_32(uint32_t value)
{
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return tab32[(uint32_t)(value * 0x07C4ACDD) >> 27];
}

void fib(uint32_t n, mpz_t **output) {
    mpz_t m0i, m1i, t0i;
    mpz_inits(m0i, m1i, t0i);
    mpz_set_ui(m0i, 0);
    mpz_set_ui(m1i, 1);
    mpz_t *m0 = &m0i;
    mpz_t *m1 = &m1i;
    mpz_t *t0 = &t0i;
    
    for (uint8_t i = log2_32(n); i >= 0, i--;) {
        mpz_mul(*t0, *m1, *m1);

        mpz_add(*m1, *m1, *m1);
        mpz_mul(*m1, *m1, *m0);
        mpz_add(*m1, *m1, *t0);

        mpz_mul(*m0, *m0, *m0);
        mpz_add(*m0, *m0, *t0);
        if (n & (1 << i)) {
            t0 = m0;
            m0 = m1;
            m1 = t0;
            mpz_add(*m1, *m1, *m0);
        }
    }

    printf("hello");
    *output = m0;

    printf("hello");
    mpz_clear(m1i);
    mpz_clear(t0i);
    printf("hello");
}


int main() {
    // FILE *filed;
    int n = 10;

    clock_t before = clock();
    mpz_t **output;
    printf("hello");
    fib(n, output);
    printf("hello");
    clock_t after = clock();
    gmp_printf("%Zd\n", **output);
    printf("It took %d ms to calculate the %dth fibonacci number.", (after - before) * 1000 / CLOCKS_PER_SEC, n);

    // filed = fopen("fib.txt", "w");
    // gmp_printf("%Zd", output);

    mpz_clear(**output);
    // fclose(filed);
    
    return 0;
}