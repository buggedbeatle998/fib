#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "gmp.h"


const uint8_t tab32[32] = {
     0,  9,  1, 10, 13, 21,  2, 29,
    11, 14, 16, 18, 22, 25,  3, 30,
     8, 12, 20, 28, 15, 17, 24,  7,
    19, 27, 23,  6, 26,  5,  4, 31
};


/// @brief Quickly Finds log2 of a 32-bit uint
/// @param value 
/// @return log2(value)
uint32_t log2_32(uint32_t value) {
    // Bit-twiddling to quickly find log2 of a 32-bit uint.
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return tab32[(uint32_t)(value * 0x07C4ACDD) >> 27];
}


/// @brief Finds log10 of big number x
/// @param value
/// @return log10(value)
double biginteger_log_modified(mpz_t value) {
    // A neat trick to get the log10 of a big number.
    signed long int exponent;
    const double mantissa = mpz_get_d_2exp(&exponent, value);
    return log10(mantissa) + log10(2) * (double) exponent;
}


/// @brief Finds the nth Fibonacci number
/// @param n
void fib(uint32_t n, bool benchmark) {
    if (n > 1) {
        clock_t before = clock();
        mpz_t m0, m1, t0;
        mpz_inits(m0, m1, t0, NULL);
        // Here m0 and m1 represent the top and bottom values of a 1x2 matrix.
        // These are the 0th and 1st numbers of the Fibonacci sequence
        // When a matrix is multiplied by this matrix with our custom box product,
        // The bottom value set to the addition of both values and the top value is
        // set to the previous bottom value. this iterates the Fibonacci sequence.
        // t0 is a temporary variable for calculations
        mpz_set_ui(m0, 0);
        mpz_set_ui(m1, 1);
        uint32_t i = log2_32(n);
        bool is_neg = true;

        // Here, we will raise our matrix to the power of n which will increment
        // the Fibonacci sequence n times.
        // We are using 2^k-ary binary exponentiation to achive this.
        while (i--) {
            // Square the matrix.
            // (a) ☒ (a) = a(a ) + (b^2)(1)
            // (b)   (b)    (2b)        (1)
            // Orig
            //mpz_mul(t0, m1, m1);
            //
            //mpz_mul(m1, m1, m0);
            //mpz_add(m1, m1, m1);
            //mpz_add(m1, m1, t0);

            //mpz_mul(m0, m0, m0);
            //mpz_add(m0, m0, t0);
            mpz_mul(t0, m0, m0);
            mpz_mul(m0, m1, m1);
            mpz_mul_2exp(m1, m0, 2);
            mpz_sub(m1, m1, t0);
            if (is_neg)
                mpz_sub_ui(m1, m1, 2);
            else
                mpz_add_ui(m1, m1, 2);
            mpz_add(m0, m0, t0);

            if ((is_neg = n & (1 << i))) {
                // Multiply the matrix by the original matrix.
                // (a) ☒ (c) = a(c) + (bd)(1) + bc(0)
                // (b)    (d)    (d)       (1)     (1)
                // However this simplifies is just incrementing the Fibonacci sequence once.
                mpz_sub(m0, m1, m0);
            } else {
                mpz_sub(m1, m1, m0);
            }
            //gmp_printf("%Zd\n%Zd\n\n", m1, m0);
        }

        clock_t after = clock();
        if (benchmark) {
            printf("%ld", (after - before) * 1000 / CLOCKS_PER_SEC);
        } else {
            gmp_printf("%Zd\n", m1);
            printf("This number has %llu digits\n", (uint64_t)biginteger_log_modified(m1) + 1);
            printf("This number has %llu bits\n", (uint64_t)mpz_sizeinbase(m1, 2));
            printf("It took %ld ms to calculate the %dth fibonacci number.\n", (after - before) * 1000 / CLOCKS_PER_SEC, n);
        }
        mpz_clears(m0, m1, t0, NULL);
    } else {
        // Base case.
        if (benchmark) {
            printf("%ld", 0.0);
        } else {
            //printf("%d\n", n);
            printf("This number has 1 digit\n");
            printf("It was Instant to calculate the %dth fibonacci number.\n", n);
        }
    }
}


int main(int argc, char **argv) {
    // Gets number from command-line args.
    fib(atoi(argv[1]), argc >= 3);

    return 0;
}
