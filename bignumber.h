#ifndef BIGNUMBER_H
#define BIGNUMBER_H

/**
 * @struct Node
 * @brief A node in a doubly linked list representing a single digit of a large
 * number.
 */
typedef struct Node {
    struct Node *prev;
    int digit;
    struct Node *next;
} Node;

/**
 * @struct BigNumber
 * @brief Represents a large number using a doubly linked list.
 */
typedef struct {
    Node *head;
    Node *tail;
    int sign;
} BigNumber;

BigNumber *bignumber(void);

/**
 * @brief Inserts a string of digits into a BigNumber type.
 *
 * @param digit_string - char pointer string of digits to be inserted into the
 * BigNumber.
 * @param bn - pointer to the BigNumber object where the digits will be
 * inserted.
 */
void bignumber_insert_string(BigNumber *bn, char *digit_string);
char *read_line(void);

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
int bignumber_calculator(void);

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
                              BigNumber *C);

/**
 * @brief Frees the allocated memory of a BigNumber.
 *
 * @param bn pointer to the BigNumber object to be freed.
 */
void bignumber_free(BigNumber *bn);

/**
 * @brief Prints a BigNumber.
 *
 * @param bn - A pointer to the BigNumber that will be printed.
 */
void bignumber_print(BigNumber *bn);

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
BigNumber *bignumber_add(BigNumber *A, BigNumber *B);

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
BigNumber *bignumber_subtract(BigNumber *A, BigNumber *B);

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
BigNumber *bignumber_multiplication(BigNumber *A, BigNumber *B);

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
BigNumber *bignumber_division(BigNumber *A, BigNumber *B);

#endif
