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

// Reverse a BigNumber to help in operations
void bignumber_reverse(BigNumber *bn) {
    Node *curr_node = bn->head;
    Node *temp = NULL;

    while (curr_node != NULL) {
        temp = curr_node->prev;
        curr_node->prev = curr_node->next;
        curr_node->next = temp;

        curr_node = curr_node->prev;
    }

    // Update list head
    if (temp != NULL) {
        bn->head = temp->prev;
    }
}

// Add two BigNumbers and returns the sum
BigNumber *bignumber_add(BigNumber *A, BigNumber *B) {
    BigNumber *C = (BigNumber *)malloc(sizeof(BigNumber));
    int carry = 0, sum = 0;

    bignumber_reverse(A);
    bignumber_reverse(B);
    
    Node *curr_node_A = A->head;
    Node *curr_node_B = B->head;
    
    while (curr_node_A != NULL || curr_node_B != NULL || carry != 0) {
        // Verify if any number has reached its end
        int digitA = (curr_node_A != NULL) ? curr_node_A->digit : 0;
        int digitB = (curr_node_B != NULL) ? curr_node_B->digit : 0;
        
        sum = digitA + digitB + carry;
        carry = sum / 10;
        bignumber_insert(C, sum % 10);
        
        // Proceed to the next node if 
        if (curr_node_A != NULL) curr_node_A = curr_node_A->next;
        if (curr_node_B != NULL) curr_node_B = curr_node_B->next;
    }
    
    bignumber_reverse(C);
    
    return C;
}

BigNumber bignumber_subtract(BigNumber *A, BigNumber *B)
{
    return BigNumber();
}
