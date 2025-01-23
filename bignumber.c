#include "bignumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
BigNumber *bignumber_add(BigNumber *A, BigNumber *B);
BigNumber *bignumber_subtract(BigNumber *A, BigNumber *B);

/**
 * @brief Creates and returns a new BigNumber.
 *
 * @return new BigNumber instance.
 */
BigNumber *bignumber(void) {
    BigNumber *bn = (BigNumber *)malloc(sizeof(BigNumber));
    bn->head = NULL;
    bn->tail = NULL;
    bn->sign = 1;
    return bn;
}

/**
 * @brief Inserts a digit into a BigNumber type
 *
 * @param n - integer digit
 * @param bn - pointer to the BigNumber object where the digit will be
 * inserted.
 */
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

/**
 * @brief Inserts a string of digits into a BigNumber type.
 *
 * @param digit_string - char pointer string of digits to be inserted into the
 * BigNumber.
 * @param bn - pointer to the BigNumber object where the digits will be
 * inserted.
 */
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

/**
 * @brief Reads one line of standard input.
 */
char *read_line(void) {
    char *line = NULL;
    size_t len = 0;
    size_t read;

    read = getline(&line, &len, stdin);
    if (read == -1) {
        free(line);
        return NULL;
    }

    // Remove o \n do final da linha
    if (line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }

    return line;
}

/**
 * @brief Realizes the operation based on the operator and BigNumbers.
 *
 * This function performs an operation on the given BigNumber objects based on
 * the specified operator.
 *
 * @param operator The operator used to determine the operation
 * ('+', '-', '*' and '/').
 * @param A - pointer to the first BigNumber operand.
 * @param B - pointer to the second BigNumber operand.
 * @param C - pointer to the result bigNumber
 *
 * @return pointer to a BigNumber object representing the result of the
 * operation.
 */
BigNumber *operation_realized(char operator, BigNumber * A, BigNumber *B,
                              BigNumber *C) {
    if (operator== '+') {
        C = bignumber_add(A, B);
    } else if (operator== '-') {
        C = bignumber_subtract(A, B);
    } else if (operator== '*') {
        C = bignumber_multiplication(A, B);
    } else if (operator== '/') {
        C = bignumber_division(A, B);
    } else if (operator== '%') {
        // C = bignumber_remainder(A, B);
        printf(
            "Operador '%c' não declarado em 'operation_realized'!\n", operator);
    } else if (operator== '^') {
        printf(
            "Operador '%c' não declarado em 'operation_realized'!\n", operator);
    } else {
        printf("Operador '%c' não suportado!\n", operator);
    }
    return C;
}

/**
 * @brief Reads input for two BigNumbers and an operator, performs the
 * operation, and prints the result.
 *
 * This function continuously reads input consisting of two BigNumbers and an
 * operator (addition, subtraction, multiplication, or division). It performs
 * the specified operation on the BigNumbers and prints the result. Memory is
 * managed by freeing the BigNumbers and input strings after each operation.
 *
 * @return 1 if the calculation process completes successfully.
 */
int bignumber_calculator(void) {
    char *first_line, *second_line, *third_line;
    BigNumber *A, *B, *C;

    while (1) {
        // Read the first three lines
        first_line = read_line();

        if (first_line == NULL)
            break;

        if (first_line[0] == '\0') {
            free(first_line);
            break;
        }

        second_line = read_line();
        if (second_line == NULL) {
            free(first_line);
            break;
        }

        third_line = read_line();
        if (third_line == NULL) {
            free(first_line);
            free(second_line);
            break;
        }

        char operator= third_line[0];

        // Create bignumbers and insert the values
        A = bignumber();
        B = bignumber();

        bignumber_insert_string(A, first_line);
        bignumber_insert_string(B, second_line);

        C = operation_realized(operator, A, B, C);

        bignumber_print(C);

        bignumber_free(A);
        bignumber_free(B);
        bignumber_free(C);

        // Free memory
        free(first_line);
        free(second_line);
        free(third_line);
    }
    return 1;
}

/**
 * @brief Frees the allocated memory of a BigNumber.
 *
 * @param bn pointer to the BigNumber object to be freed.
 */
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

/**
 * @brief Prints a BigNumber.
 *
 * @param bn - A pointer to the BigNumber that will be printed.
 */
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

/**
 * @brief Reverses a BigNumber to assist in operations.
 *
 * @param bn - A pointer to the BigNumber that will be reversed.
 */
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

/**
 * @brief Removes all leading zeros from a BigNumber.
 *
 * @param bn pointer to the BigNumber object whose leading zeros will be
 * removed.
 */
void bignumber_remove_left_zeros(BigNumber *bn) {
    Node *curr_node = bn->head;
    while (curr_node && curr_node->digit == 0) {
        Node *next_node = curr_node->next;
        free(curr_node);
        curr_node = next_node;
        if (curr_node)
            curr_node->prev = NULL;
    }
    bn->head = curr_node;

    // If the number was made of zeros, make it 0
    if (!bn->head) {
        bn->tail = NULL;
        bignumber_insert(bn, 0); // Result is 0
    }
}

BigNumber *bignumber_copy_value(BigNumber *original) {
    BigNumber *copy = bignumber();

    Node *original_current_node = original->head;
    while (original_current_node) {
        bignumber_insert(copy, original_current_node->digit);
        original_current_node = original_current_node->next;
    }

    copy->sign = original->sign;

    return copy;
}

/**
 * @brief Compares two BigNumbers (A and B).
 *
 * This function compares two BigNumber objects and returns:
 * --> `1` if 'A' is greater than or equal to 'B',
 * --> `-1` if 'A' is less than B''
 *
 * @param A A pointer to the first BigNumber to be compared.
 * @param B A pointer to the second BigNumber to be compared.
 *
 * @return 1 if A is greater than or equal to B, -1 if A is less than B.
 */
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
    while (curr_node_A) {
        lenA++;
        curr_node_A = curr_node_A->next;
    }
    while (curr_node_B) {
        lenB++;
        curr_node_B = curr_node_B->next;
    }

    if (lenA > lenB)
        return A->sign == 1 ? 1 : -1;
    if (lenA < lenB)
        return A->sign == 1 ? -1 : 1;

    // Compare digit by digit
    curr_node_A = A->head;
    curr_node_B = B->head;
    while (curr_node_A && curr_node_B) {
        if (curr_node_A->digit > curr_node_B->digit)
            return A->sign == 1 ? 1 : -1;
        if (curr_node_A->digit < curr_node_B->digit)
            return A->sign == 1 ? -1 : 1;
        curr_node_A = curr_node_A->next;
        curr_node_B = curr_node_B->next;
    }

    return 1; // Numbers are equal
}

/**
 * @brief Adds two BigNumbers (A and B) and returns the result.
 *
 * This function handles addition of two BigNumbers, considering their signs.
 * If the numbers have opposite signs, it performs a subtraction instead.
 *
 * @param A A pointer to the first BigNumber.
 * @param B A pointer to the second BigNumber.
 *
 * @return A pointer to a new BigNumber representing the sum of A and B.
 *         The result's sign is determined based on the signs of A and B.
 */
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
        if (curr_node_A != NULL)
            curr_node_A = curr_node_A->next;
        if (curr_node_B != NULL)
            curr_node_B = curr_node_B->next;
    }

    bignumber_reverse(A);
    bignumber_reverse(B);
    bignumber_reverse(C);

    // Apply sign to the result
    C->sign = A->sign;

    return C;
}

/**
 * @brief Subtracts one BigNumber (B) from another (A) and returns the result.
 *
 * This function handles subtraction of two BigNumbers, considering their signs.
 *
 * @param A A pointer to the first BigNumber (minuend).
 * @param B A pointer to the second BigNumber (subtrahend).
 *
 * @return A pointer to a new BigNumber representing the difference of A and B.
 *         The result's sign is adjusted based on the relative size of A and B.
 */
BigNumber *bignumber_subtract(BigNumber *A, BigNumber *B) {
    BigNumber *C = bignumber();

    // Verify if a addition operation would be suitable
    if (A->sign * B->sign == -1) {
        int a_swap = 0;
        int b_swap = 0;
        if (B->sign == -1) {
            b_swap = 1;
            B->sign = 1;
        } else if (A->sign == -1) {
            a_swap = 1;
            A->sign = 1;
        }

        C = bignumber_add(A, B);

        if (b_swap == 1) {
            B->sign = -1;
        } else if (a_swap == 1) {
            A->sign = -1;
        }
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

    int swap_signs = 0;
    if (A->sign == -1 && B->sign == -1) {
        swap_signs = 1;
        A->sign = 1;
        B->sign = 1;
    }

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

    if (swap_signs) {
        A->sign = -1;
        B->sign = -1;
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

        if (curr_node_A != NULL)
            curr_node_A = curr_node_A->next;
        if (curr_node_B != NULL)
            curr_node_B = curr_node_B->next;
    }

    bignumber_reverse(A);
    bignumber_reverse(B);
    bignumber_reverse(C);

    // Remove leading zeros
    bignumber_remove_left_zeros(C);

    // Apply sign to the result
    if (A->sign == -1 && B->sign == -1 && bignumber_compare(A, B) == -1) {
        C->sign = -1;
    } else {
        C->sign = bignumber_compare(A, B);
    }

    return C;
}

/**
 * @brief Multiplies two BigNumbers (A and B) and returns the result.
 *
 * This function performs the multiplication of two BigNumbers, handling the
 * carry and zeros at the end of the result. If either of the numbers is zero,
 * the result is set to zero. The result's sign is determined based on the signs
 * of A and B.
 *
 * @param A A pointer to the first BigNumber (multiplicand).
 * @param B A pointer to the second BigNumber (multiplier).
 *
 * @return A pointer to a new BigNumber representing the product of A and B.
 *         The result's sign is adjusted based on the signs of A and B.
 */
BigNumber *bignumber_multiplication(BigNumber *A, BigNumber *B) {
    BigNumber *result = bignumber();

    // Check if any of the numbers is zero
    if ((A->head->digit == 0 && A->head->next == NULL) ||
        (B->head->digit == 0 && B->head->next == NULL)) {
        bignumber_insert(result, 0);
        return result;
    }

    bignumber_reverse(A);
    bignumber_reverse(B);

    Node *curr_node_A = A->head;
    Node *curr_node_B = B->head;

    int zerosAtTheEnd = 0;

    // for each A digit
    while (curr_node_A != NULL) {
        BigNumber *accumulator = bignumber();
        int product;
        int carry = 0;

        // Add left zeroes
        for (int i = 0; i < zerosAtTheEnd; i++) {
            bignumber_insert(accumulator, 0);
        }

        curr_node_B = B->head; // Reset A digit

        // Run through and multiply A digits
        while (curr_node_B != NULL) {
            int digit_node_A = curr_node_A->digit;
            int digit_node_B = (curr_node_B != NULL) ? curr_node_B->digit : 0;

            product = (digit_node_A * digit_node_B + carry);

            bignumber_insert(accumulator, product % 10);

            carry = product / 10;

            if (curr_node_A != NULL)
                curr_node_B = curr_node_B->next;
        }

        if (carry > 0) {
            bignumber_insert(accumulator, carry);
        }

        bignumber_reverse(accumulator);

        BigNumber *new_result = bignumber_add(result, accumulator);
        bignumber_free(result);
        bignumber_free(accumulator);

        result = new_result;

        zerosAtTheEnd += 1;

        curr_node_A = curr_node_A->next;
    }

    bignumber_reverse(A);
    bignumber_reverse(B);

    // Multiplication signal
    result->sign = A->sign * B->sign;

    return result;
}

/**
 * @brief Divides one BigNumber (A) by another (B) and returns the quotient.
 *
 * This function performs division of two BigNumbers, calculating the quotient
 * by repeatedly comparing digits and adjusting based on the result of the
 * division.
 *
 * @param A A pointer to the BigNumber to be divided (dividend).
 * @param B A pointer to the BigNumber by which A is divided (divisor).
 *
 * @return A pointer to a new BigNumber representing the quotient of A divided
 * by B.
 */
BigNumber *bignumber_division(BigNumber *A, BigNumber *B) {
    BigNumber *result = bignumber();

    // work with positive numbers, and after return correctly
    int result_sign = A->sign * B->sign;
    int original_A_sign = A->sign;
    int original_B_sign = B->sign;
    A->sign = 1;
    B->sign = 1;

    // If A < B, result is 0
    if (bignumber_compare(A, B) == -1) {
        bignumber_insert(result, 0);

        A->sign = original_A_sign;
        B->sign = original_B_sign;
        return result;
    }

    // working with a copy of A
    BigNumber *dividend = bignumber_copy_value(A);
    BigNumber *current_dividend = bignumber();
    Node *curr_node = dividend->head;

    while (curr_node != NULL) {
        bignumber_insert(current_dividend, curr_node->digit);
        int result_digit = 0;
        while (bignumber_compare(current_dividend, B) >= 0) {
            BigNumber *temporary = bignumber_subtract(current_dividend, B);
            bignumber_free(current_dividend);
            current_dividend = bignumber_copy_value(temporary);
            result_digit++;
        }

        bignumber_insert(result, result_digit);
        curr_node = curr_node->next;
    }

    bignumber_free(dividend);
    bignumber_free(current_dividend);

    bignumber_remove_left_zeros(result);
    result->sign = result_sign;

    // Restore original signs
    A->sign = original_A_sign;
    B->sign = original_B_sign;

    return result;
}