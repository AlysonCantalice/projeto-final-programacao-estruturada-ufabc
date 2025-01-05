#ifndef BIGNUMBER_H
#define BIGNUMBER_H

typedef struct {
    int *digits;
    int n_elements;
    int sign;
} _bignum;
typedef _bignum *BigNumber;

BigNumber create_bignumber(void);

#endif