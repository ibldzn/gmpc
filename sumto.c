#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

// calculate the result of sum to `n`
// "sum_to(n) = (n * (n + 1)) / 2"
void sum_to(const mpz_t n, mpz_t out)
{
    mpz_t v;
    mpz_init(v);

    // v = n + 1
    mpz_add_ui(v, n, 1);
    // out = n * v
    mpz_mul(out, n, v);
    // out = out / 2
    mpz_divexact_ui(out, out, 2);

    mpz_clear(v);
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
    sum_to(n, result);

    char* res_str = mpz_get_str(NULL, 10, result);
    puts(res_str);
    free(res_str);

    mpz_clear(result);
    mpz_clear(n);
}
