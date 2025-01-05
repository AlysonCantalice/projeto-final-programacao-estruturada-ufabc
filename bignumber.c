#include <stdlib.h>
#include "bignumber.h"

// Creates and returns a new BigNumber 
BigNumber* bignumber(void) {
    BigNumber *bn = (BigNumber *)malloc(sizeof(BigNumber));
    bn->head = NULL;
    bn->tail = NULL;
    bn->sign = 1;
    return bn;
}

// Inserts a digit into a BigNumber type
void bignumber_insert(BigNumber *bn, int n) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->digit = n;
    new_node->next = NULL;

    // Checks if list if empty
    if (bn->head == NULL) {
        new_node->prev = NULL;
        bn->head = new_node;
        bn->tail = new_node;
    } else {
        new_node->prev = bn->tail;
        bn->tail->next = new_node;
        bn->tail = new_node;
    }
}

// Frees the allocated memory of a BigNumber
void bignumber_free(BigNumber *bn) {
    Node *curr_node = bn->head;
    Node *next_node;

    while (curr_node != NULL) {
        next_node = curr_node->next;
        free(curr_node);
        curr_node = next_node;
    }

    free(bn);
}

void bignumber_print(BigNumber *bn) {
    if (bn->sign == -1) {
        printf("-");
    }

    Node *curr_node = bn->head;
    while (curr_node != NULL) {
        printf("%d", curr_node->digit);
        curr_node = curr_node->next;
    }
    printf("\n");
}