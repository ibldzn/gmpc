#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

// calculate `n`-th fibonacci
void fibonacci(const mpz_t n, mpz_t out)
{
    // unnecessary but whatever
    mpz_set_ui(out, 0);

    const int cmp = mpz_cmp_ui(n, 1);
    // if n == 0, return 1
    // else if n < 0, return 0 (should probably raise an error but this should do it for now)
    if (cmp == 0) {
        mpz_set_ui(out, 1);
        return;
    } else if (cmp < 0) {
        mpz_set_ui(out, 0);
        return;
    }

    mpz_t iterator, last, curr;
    mpz_init_set_ui(iterator, 1);
    mpz_init_set_ui(last, 0);
    mpz_init_set_ui(curr, 1);

    //  (iterator = 1; iterator < n; ++iterator)
    for (; mpz_cmp(iterator, n) < 0; mpz_add_ui(iterator, iterator, 1)) {
        // out = last + curr
        mpz_add(out, last, curr);
        // last = curr
        mpz_set(last, curr);
        // curr = out
        mpz_set(curr, out);
    }

    mpz_clear(curr);
    mpz_clear(last);
    mpz_clear(iterator);
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [base 10 int]\n", argv[0]);
        return 1;
    }

    mpz_t n, result;
    if (mpz_init_set_str(n, argv[1], 10) == -1) {
        fprintf(stderr, "%s is not a valid base 10 int!\n", argv[1]);
        return 1;
    }

    mpz_init(result);
    fibonacci(n, result);

    char* result_str = mpz_get_str(NULL, 10, result);
    puts(result_str);
    free(result_str);

    mpz_clear(result);
    mpz_clear(n);
}
