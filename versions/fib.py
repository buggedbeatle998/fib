from math import log2, ceil
from time import time
from sys import argv, set_int_max_str_digits
set_int_max_str_digits(0)



def fib(n: int, benchmark: bool) -> None:
    if (n > 1):
        if (benchmark):
            before = time()
        m0, m1 = 0, 1
        t0 = 0
        for i in range(ceil(log2(n)))[::-1]:
            t0 = m1 * m1

            m1 = m1 + m1
            m1 = m1 * m0
            m1 = m1 + t0

            m0 = m0 * m0
            m0 = m0 * t0

            if (n & (1 << i)):
                m0, m1 = m1, m0
                m1 = m1 + m0
        if (benchmark):
            print(time() - before, end="")
        else:
            print(m1)
    else:
        if (benchmark):
            print(0, end="")
        else:
            print(n)


if __name__ == "__main__":
    fib(int(argv[1]), len(argv) >= 3 and argv[2])
