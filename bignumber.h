#ifndef BIGNUMBER_H
#define BIGNUMBER_H

typedef struct Node {
    struct Node *prev;
    int digit;        
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int sign;
} BigNumber;

BigNumber *bignumber(void);
void bignumber_insert(BigNumber *bn, int n);
void bignumber_free(BigNumber *bn);
void bignumber_print(BigNumber *bn);

BigNumber *bignumber_add(BigNumber *A, BigNumber *B);
BigNumber *bignumber_subtract(BigNumber *A, BigNumber *B);

void bignumber_reverse(BigNumber *bn);
void bignumber_remove_left_zeros(BigNumber *bn);
int bignumber_compare(BigNumber *A, BigNumber *B);

#endif
