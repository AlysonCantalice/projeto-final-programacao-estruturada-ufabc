#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bignumber.h"

// Prototypes
BigNumber *bignumber_add(BigNumber *A, BigNumber *B);
BigNumber *bignumber_subtract(BigNumber *A, BigNumber *B);

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

// Inserts a string of digits into a BigNumber type
void bignumber_insert_string(BigNumber *bn, char *digit_string) {
    int digit_size = strlen(digit_string);
    
    for (int i = 0; i < digit_size; i++) {
        if (digit_string[i] == '-') {
            bn->sign = -1;
        } else {
            bignumber_insert(bn, digit_string[i] - '0');
        }
    }
}

// read the input file 
FILE *read_file(int argc, char *argv[]){
    // Verifica se o nome do arquivo foi passado como argumento
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo de entrada
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
    }   
    // fclose(inputFile);
    return inputFile;
}

// print the result of the file data, line by line 
void print_file_results(FILE *input_file){
    size_t len1 = 0, len2 = 0; // Comprimento inicial das strings
    char *num1 = NULL; // Ponteiro para a string do primeiro número
    char *num2 = NULL; // Ponteiro para a string do segundo número
    char operator;
    // int operacoes = 0;
    BigNumber *A, *B, *C;

    while (1) {
        // Lê o primeiro número
        if (getline(&num1, &len1, input_file) == -1) break;
        num1[strcspn(num1, "\n")] = '\0'; // Remove o '\n'

        // Lê o segundo número
        if (getline(&num2, &len2, input_file) == -1) break;
        num2[strcspn(num2, "\n")] = '\0'; // Remove o '\n'

        // Lê o operador
        if (fscanf(input_file, " %c\n", &operator) != 1) break;
        
        // operacoes += 1;

        // Cria BigNumbers e insere os valores lidos
        A = bignumber();
        B = bignumber();
        C = bignumber();

        bignumber_insert_string(A, num1);
        bignumber_insert_string(B, num2);

        C = operation_realized(operator, A, B, C);

        bignumber_print(C);

        free(A);
        free(B);
        free(C);
    }
}

// Realize the operation based on the operator
BigNumber* operation_realized(char operator, BigNumber *A, BigNumber *B, BigNumber *C){
    // Realiza o cálculo com base no operador
    if (operator == '+') {
        C = bignumber_add(A, B);
    } 
    else if (operator == '-') {
        C = bignumber_subtract(A, B);
    }
    else if (operator == '*') {
        // C = bignumber_add(A, B);
        printf("Operador '%c' não declarado em 'operation_realized'!\n", operator);
    }
    else if (operator == '/') {
        // C = bignumber_add(A, B);
        printf("Operador '%c' não declarado em 'operation_realized'!\n", operator);
    }
    else if (operator == '%') {
        // C = bignumber_add(A, B);
        printf("Operador '%c' não declarado em 'operation_realized'!\n", operator);
    }
    else if (operator == '^') {
        // C = bignumber_add(A, B);
        printf("Operador '%c' não declarado em 'operation_realized'!\n", operator);
    } else {
        printf("Operador '%c' não suportado!\n", operator);
    }
    return C;
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

// Prints a BigNumber
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

BigNumber *bignumber_copy_value(BigNumber *original) {
    BigNumber *copy = bignumber();

    Node *original_current_node = original->head;  
    while (original_current_node) {
        bignumber_insert(copy, original_current_node->digit);
        original_current_node = original_current_node->next;
    }

    return copy;
}


// Add two BigNumbers and returns the sum
BigNumber *bignumber_add(BigNumber *A, BigNumber *B) {
    BigNumber *C = bignumber();
    
    // Verify if a subtraction operation would be suitable
    if (A->sign * B->sign == -1) {
        if (A->sign == -1) {
            A->sign = 1;
            C = bignumber_subtract(B, A);
            A->sign = -1;
        } else {
            B->sign = 1;
            C = bignumber_subtract(A, B);
            B->sign = -1;
        }
        
        return C;
    }
    
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
    
    // Apply sign to the result
    C->sign = A->sign;

    return C;
}

BigNumber *bignumber_subtract(BigNumber *A, BigNumber *B) {
    BigNumber *C = bignumber();
    
    // Verify if a addition operation would be suitable
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

    while (curr_node_A != NULL || curr_node_B != NULL) {
        int digitA = (curr_node_A != NULL) ? curr_node_A->digit : 0;
        int digitB = (curr_node_B != NULL) ? curr_node_B->digit : 0;

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