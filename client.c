#include <stdio.h>
#include "bignumber.h"
#include <stdlib.h>

// Rodar o executavel com valores fixos no código

// int main() {

//     BigNumber *A = bignumber();
//     BigNumber *B = bignumber();
    
//     bignumber_insert(A, 3);
//     bignumber_insert(A, 5);

//     bignumber_insert(B, 4);
//     bignumber_insert(B, 1);
    
//     BigNumber *C = bignumber_add(A, B);

//     bignumber_print(C);

//     return 0;
// }

// Rodar o executavel com o input sendo um arquivo

// ainda esta com erro pois nao esta lendo numero por numero para armazenar no BigNumber
// para rodar com gdb: (para funcionar, precisa alterar para: argc != 1 e fopen(argv[0])) 
// gdb ./program
// run < teste.txt

int main(int argc, char *argv[]) {
    // Verifica se o nome do arquivo foi passado como argumento
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo de entrada
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    // Criação das variáveis BigNumber
    BigNumber *A = bignumber();
    BigNumber *B = bignumber();
    BigNumber *C = bignumber();

    int num1, num2;
    char operator;

    // Lê o arquivo até o final
    while (fscanf(inputFile, "%d", &num1) != EOF) {

        // Insere o primeiro número na lista A
        bignumber_insert(A, num1);

        // Lê o próximo número
        if (fscanf(inputFile, "%d", &num2) != EOF) {
            // Insere o segundo número na lista B
            bignumber_insert(B, num2);
        }

        // getchar();

        // Lê o operador
        if (fscanf(inputFile, " %c", &operator) != EOF) {
            if (operator == '+') {
                // Realiza a soma e armazena em C
                C = bignumber_add(A, B);
            }
        }

        bignumber_print(C);
        // printf("\n");
    }

    // Fecha o arquivo
    fclose(inputFile);

    // // Libera memória
    bignumber_free(A);
    bignumber_free(B);
    bignumber_free(C);

    return 0;
}
