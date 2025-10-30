#include "gmp.h"
#include <time.h>
#include <stdio.h>


int main(void) {
    clock_t before = clock();
    mpz_t m0;
    mpz_init(m0);
    mpz_fib_ui(m0, 1000000000);
    clock_t after = clock();
    printf("%ld", (after - before) * 1000 / CLOCKS_PER_SEC);
    mpz_clear(m0);
}
