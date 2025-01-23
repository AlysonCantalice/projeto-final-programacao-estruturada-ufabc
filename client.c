#include "bignumber.h"
#include <stdio.h>
#include <stdlib.h>

// ENTRADAS E SAÍDAS:
// A entrada para o seu programa é fornecida via a entrada padrão (teclado do
// usuário) e o seu programa deve fornecer a saída na saída padrão (escrever na
// tela).

// VAZAMENTO DE MEMÓRIA PARA SOMA E SUBTRAÇÃO ESTÁ OK.
// valgrind --leak-check=yes ./program ./tests/instances/04_small_pos_minus.in

// para rodar com gdb: (para funcionar, precisa alterar read_file() para: argc
// != 1 e fopen(argv[0])) gdb ./program run < teste.txt

// TESTE 1 AO 14 PASSOU. O 15 DEU ERRO!
// $ rm out.txt
// $ ./program < ./tests/instances/10_small_minus.in >> out.txt
// $ diff out.txt ./tests/instances/10_small_minus.out

// • bignumber.h um arquivo de header de C contendo toda a interface pública do
// seu tipo BigNumber. • bignumber.c um arquivo de C contendo a implementação da
// sua interface pública. • client.c um arquivo de C contendo a função main() e
// que é responsável por usar a sua biblioteca bignumber.h para resolver o
// problema do projeto. • makefile um arquivo de configuração que permita o
// programa make compilar corretamente o seu programa quando o seguinte comando
// for digitado dentro do diretório xxxxx: make

// -----------------------------------------
// Iniciar a instância de calculadora de BigNumber

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

// -----------------------------------------
// Iniciar a instância de calculadora de BigNumber

// int main(){

//     bignumber_calculator();

//     return 0;
// }