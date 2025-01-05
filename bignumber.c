#include <stdlib.h>
#include "bignumber.h"

// Creates and returns a new BigNumber 
BigNumber create_bignumber(void)
{
    BigNumber bn = malloc(sizeof(BigNumber));
    bn->digits = malloc(sizeof(int));
    bn->n_elements = 0;
    bn->sign = 1;
    return bn;
}

// Inserts a digit into a BigNumber type
void bignumber_insert(BigNumber bn, int n) {
    // Makes sure that theres always enough space for one more digit
    bn->digits = realloc(bn->digits, sizeof(int) * (bn->n_elements + 1));
    bn->digits[bn->n_elements] = n;
    bn->n_elements++;
}

// Frees the allocated memory of a BigNumber
void bignumber_free(BigNumber bn) {
    free(bn->digits);
    free(bn);
}