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