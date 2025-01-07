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

// Remove all zeros to the left
void bignumber_remove_left_zeros(BigNumber *bn) {
    Node *curr_node = bn->head;
    while (curr_node && curr_node->digit == 0) {
        Node *next_node = curr_node->next;
        free(curr_node);
        curr_node = next_node;
        if (curr_node) curr_node->prev = NULL;
    }
    bn->head = curr_node;
    
    // If the number was made of zeros, make it 0
    if (!bn->head) {
        bn->tail = NULL;
        bignumber_insert(bn, 0);  // Result is 0
    }
}

// Compare if A => B, return 1. if A < B, return -1.
int bignumber_compare(BigNumber *A, BigNumber *B) {
    // First, compare signs
    if (A->sign > B->sign) {
        return 1;
    } else if (B->sign > A->sign) {
        return -1;
    }
    
    Node *curr_node_A = A->head;
    Node *curr_node_B = B->head;

    // Compare lengths
    int lenA = 0, lenB = 0;
    while (curr_node_A) { lenA++; curr_node_A = curr_node_A->next; }
    while (curr_node_B) { lenB++; curr_node_B = curr_node_B->next; }
    
    if (lenA > lenB) {
        return 1;
    } else if (lenB > lenA) {
        return -1;
    }

    // Compare digit by digit
    curr_node_A = A->head;
    curr_node_B = B->head;
    while (curr_node_A && curr_node_B) {
        if (curr_node_A->digit != curr_node_B->digit) {
            if (curr_node_A->digit > curr_node_B->digit) {
                return 1;
            } else if (curr_node_A->digit < curr_node_B->digit){
                return -1;
            }
        }
        curr_node_A = curr_node_A->next;
        curr_node_B = curr_node_B->next;
    }

    return 1;  // Numbers are equal
}

// Add two BigNumbers and returns the sum
BigNumber *bignumber_add(BigNumber *A, BigNumber *B) {
    BigNumber *C = bignumber();
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
    
    bignumber_reverse(A);
    bignumber_reverse(B);
    bignumber_reverse(C);
    
    return C;
}


BigNumber *bignumber_subtract(BigNumber *A, BigNumber *B) {
    BigNumber *C = bignumber();
    
    if (A->sign * B->sign == -1) {
        C = bignumber_add(A, B);
        if (B->sign == -1) {
            C->sign = 1;
        } else {
            C->sign = -1;
        }
        return C;
    }
    
    int borrow = 0, diff = 0;

    bignumber_remove_left_zeros(A);
    bignumber_remove_left_zeros(B);
    
    Node *curr_node_A;
    Node *curr_node_B;
    
    // Swap A with B if B > A
    if (bignumber_compare(A, B) == -1) {
        bignumber_reverse(A);
        bignumber_reverse(B);
        
        curr_node_A = B->head;
        curr_node_B = A->head;
    } else {
        bignumber_reverse(A);
        bignumber_reverse(B);
        
        curr_node_A = A->head;
        curr_node_B = B->head;
    }

    //bignumber_print(A);
    //bignumber_print(B);

    while (curr_node_A != NULL || curr_node_B != NULL) {
        int digitA = (curr_node_A != NULL) ? curr_node_A->digit : 0;
        int digitB = (curr_node_B != NULL) ? curr_node_B->digit : 0;

        // printf("A: %d, B: %d\n", digitA, digitB);
        diff = digitA - digitB - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        bignumber_insert(C, diff);

        if (curr_node_A != NULL) curr_node_A = curr_node_A->next;
        if (curr_node_B != NULL) curr_node_B = curr_node_B->next;
    }

    bignumber_reverse(A);
    bignumber_reverse(B);
    bignumber_reverse(C);

    // Remove leading zeros
    bignumber_remove_left_zeros(C);

    // Apply sign to the result
    if (A->sign == -1 && A->sign == -1 && bignumber_compare(A, B) == -1) {
        C->sign = 1;
    } else {
        C->sign = bignumber_compare(A, B);
    }

    return C;
}