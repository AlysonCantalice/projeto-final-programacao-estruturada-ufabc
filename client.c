#include "bignumber.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *first_line, *second_line, *third_line;
    BigNumber *A, *B, *C;

    while (1) {
        // read 3 lines of input (first, second and third)
        first_line = read_line();

        // to finish the program using a file when doesn't have input
        if (first_line == NULL)
            break;

        // to finish the program using the terminal when doesn't have
        // input
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

        // get the operator (+,-,*,/,%,^)
        char operator= third_line[0];

        // create BigNumbers and insert the read values
        A = bignumber();
        B = bignumber();

        bignumber_insert_string(A, first_line);
        bignumber_insert_string(B, second_line);

        // run the operation based on the bignumbers and the operator
        C = operation_realized(operator, A, B, C);

        bignumber_print(C);

        bignumber_free(A);
        bignumber_free(B);
        bignumber_free(C);

        // Frees memory allocated by reading
        free(first_line);
        free(second_line);
        free(third_line);
    }
    return 1;
}