#ifndef BIGNUMBER_H
#define BIGNUMBER_H

typedef struct {
    int *digits;
    int n_elements;
    int sign;
} _bignum;
typedef _bignum *BigNumber;

BigNumber create_bignumber(void);
void bignumber_insert(BigNumber bn, int n);
void bignumber_free(BigNumber bn);

#endif