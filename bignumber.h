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

BigNumber bignumber_add(BigNumber *A, BigNumber *B);

void bignumber_reverse(BigNumber *bn);
#endif