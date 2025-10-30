#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "gmp.h"


void fib(uint32_t n) {
    if (n > 1) {
        clock_t before = clock();
        mpz_t m0, m1;
        mpz_inits(m0, m1, NULL);
        mpz_set_ui(m0, 0);
        mpz_set_ui(m1, 1);
        while (--n) {
            mpz_swap(m0, m1);
            mpz_add(m1, m1, m0);
        }
        clock_t after = clock();
        printf("It took %ld ms to calculate the %dth fibonacci number.\n", (after - before) * 1000 / CLOCKS_PER_SEC, n);
        mpz_clears(m0, m1, NULL);
    } else {
        printf("%ld", 0.0);
    }
}


int main(int argc, char **argv) {
    fib(atoi(argv[1]));

    return 0;
}
