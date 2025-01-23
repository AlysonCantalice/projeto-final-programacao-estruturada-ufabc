#include "bignumber.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototypes
BigNumber *bignumber_add(BigNumber *A, BigNumber *B);
BigNumber *bignumber_subtract(BigNumber *A, BigNumber *B);

/**
 * @brief Creates and returns a new BigNumber.
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
        // C = bignumber_add(A, B);
        printf(
            "Operador '%c' não declarado em 'operation_realized'!\n", operator);
    } else if (operator== '^') {
        // C = bignumber_add(A, B);
        printf(
            "Operador '%c' não declarado em 'operation_realized'!\n", operator);
    } else {
        printf("Operador '%c' não suportado!\n", operator);
    }
    return C;
}

// instance of bignumber calculator
// ./program
// ./program >> output.txt
// ./program < {path_of_file}
// ./program < {path_of_file} >> output.txt
int bignumber_calculator(void) {
    char *first_line, *second_line, *third_line;
    BigNumber *A, *B, *C;

    while (1) {
        // realiza a leitura das três linhas
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

        // Cria BigNumbers e insere os valores lidos
        A = bignumber();
        B = bignumber();

        bignumber_insert_string(A, first_line);
        bignumber_insert_string(B, second_line);

        C = operation_realized(operator, A, B, C);

        bignumber_print(C);

        bignumber_free(A);
        bignumber_free(B);
        bignumber_free(C);

        // Libera a memória alocada pela leitura
        free(first_line);
        free(second_line);
        free(third_line);
    }
    return 1;
}

/**
 * @brief Frees the allocated memory of a BigNumber.
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

    if (A->sign == 1) {
        if (lenA > lenB) {
            return 1;
        } else if (lenB > lenA) {
            return -1;
        }
    } else {
        if (lenA > lenB) {
            return -1;
        } else if (lenB > lenA) {
            return 1;
        }
    }

    // Compare digit by digit
    curr_node_A = A->head;
    curr_node_B = B->head;
    if (A->sign == -1 && B->sign == -1) {
        while (curr_node_A && curr_node_B) {
            if (curr_node_A->digit != curr_node_B->digit) {
                if (curr_node_A->digit > curr_node_B->digit) {
                    return -1;
                } else if (curr_node_A->digit < curr_node_B->digit) {
                    return 1;
                }
            }
            curr_node_A = curr_node_A->next;
            curr_node_B = curr_node_B->next;
        }
    } else {
        while (curr_node_A && curr_node_B) {
            if (curr_node_A->digit != curr_node_B->digit) {
                if (curr_node_A->digit > curr_node_B->digit) {
                    return 1;
                } else if (curr_node_A->digit < curr_node_B->digit) {
                    return -1;
                }
            }
            curr_node_A = curr_node_A->next;
            curr_node_B = curr_node_B->next;
        }
    }

    return 1; // Numbers are equal
}

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

    //-2246
    //-95328

    // Apply sign to the result
    if (A->sign == -1 && B->sign == -1 && bignumber_compare(A, B) == -1) {
        C->sign = -1;
    } else {
        C->sign = bignumber_compare(A, B);
    }

    return C;
}

BigNumber *bignumber_multiplication(BigNumber *A, BigNumber *B) {
    BigNumber *result = bignumber();

    // Verifica se algum dos números é zero
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

    // para cada dígito do número A
    while (curr_node_A != NULL) {
        BigNumber *accumulator = bignumber();
        int product;
        int carry = 0;

        // Adiciona zeros à esquerda de acordo com a casa numérica
        for (int i = 0; i < zerosAtTheEnd; i++) {
            bignumber_insert(accumulator, 0);
        }

        curr_node_B = B->head; // reset do dígito do número A

        // itera e multiplica nos dígitos do número A
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

    // sinal do resultado da multiplicação
    result->sign = A->sign * B->sign;

    return result;
}

// Função para contar o número de dígitos em um BigNumber
int bignumber_length(BigNumber *bn) {
    int counter = 0;
    Node *current = bn->head;

    // Percorre a lista até o final, contando os nós (dígitos)
    while (current != NULL) {
        counter++;
        current = current->next;
    }

    return counter;
}

BigNumber *bignumber_division(BigNumber *A, BigNumber *B) {
    BigNumber *C = bignumber(); // resultado (quociente)
    // BigNumber *temp = bignumber();
    BigNumber *E = bignumber();

    if (bignumber_compare(A, B) == -1) {
        bignumber_insert(C, 0);
        return C;
    }

    bignumber_insert(C, 1);

    BigNumber *TEN = bignumber();
    bignumber_insert_string(TEN, "10");

    int first_bignumber_length = bignumber_length(A);
    int second_bignumber_length = bignumber_length(B);

    for (int i = 0; i < first_bignumber_length - second_bignumber_length; i++) {
        BigNumber *temp = bignumber_multiplication(C, TEN);
        bignumber_free(C);
        C = temp;
    }

    bignumber_print(C);

    Node *curr_node_A = A->head;
    Node *curr_node_B = B->head;
    Node *curr_node_C = C->head;

    int digit_node_A = curr_node_A->digit;
    int digit_node_B = curr_node_B->digit;

    /*
    se a > c entao valor = a/c
    se a = c entao valor = a
    se a < c entao valor = 0
    */
    if (digit_node_A > digit_node_B) {
        curr_node_C->digit = digit_node_A / digit_node_B;
    }

    if (digit_node_A == digit_node_B) {
        curr_node_C->digit = digit_node_A;
    }

    if (digit_node_A < digit_node_B) {
        curr_node_C->digit = 0;
    }

    BigNumber *D = bignumber_multiplication(C, B);

    int flag = 0;

    int result_compare = bignumber_compare(D, A); // compare '=='
    if (result_compare == 1) {
        int segunda_decimal_A = A->head->next->digit;
        int segunda_decimal_D = D->head->next->digit;

        if (segunda_decimal_A < segunda_decimal_D) {
            C->head->digit = C->head->digit - 1;
        }
    }

    if (result_compare == -1) {
        int segunda_decimal_A = A->head->next->digit;
        int segunda_decimal_D = D->head->next->digit;
    }

    int teste = bignumber_length(A);
    return teste;
}