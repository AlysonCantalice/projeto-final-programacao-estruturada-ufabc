#include <stdio.h>
#include "bignumber.h"

// ENTRADAS E SAÍDAS:
// A entrada para o seu programa é fornecida via a entrada padrão (teclado do usuário) e o seu programa
// deve fornecer a saída na saída padrão (escrever na tela).


// AINDA NÃO É ISSO QUE FOI PEDIDO PELO PROFESSOR, SÓ ESTÁ BOM PARA VALIDAR RESULTADOS


// TA COM MEMORIA VAZANDO
// valgrind --leak-check=full ./program ./tests/instances/04_small_pos_minus.in


// Rodar o executavel com o input sendo um arquivo
int main(int argc, char *argv[]){

    FILE *input_file = read_file(argc, argv);
    print_file_results(input_file);

    // NÃO ESTOU FECHANDO NA FUNÇÃO PQ SE NAO ELA NAO RETORNA O ARQUIVO
    // fclose(inputFile); 
    
    return 0;
}

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

// para rodar com gdb: (para funcionar, precisa alterar para: argc != 1 e fopen(argv[0])) 
// gdb ./program
// run < teste.txt

// int main(int argc, char *argv[]) {
//     // Verifica se o nome do arquivo foi passado como argumento
//     if (argc != 2) {
//         printf("Usage: %s <input_file>\n", argv[0]);
//         return 1;
//     }

//     // Abre o arquivo de entrada
//     FILE *inputFile = fopen(argv[1], "r");
//     if (inputFile == NULL) {
//         printf("Erro ao abrir o arquivo %s\n", argv[1]);
//         return 1;
//     }

    // Criação das variáveis BigNumber
    // BigNumber *A, *B, *C;

    // char *num1 = NULL; // Ponteiro para a string do primeiro número
    // char *num2 = NULL; // Ponteiro para a string do segundo número
    // size_t len1 = 0, len2 = 0; // Comprimento inicial das strings
    // char operator;
    // int operacoes = 0;

    // print_file_results(inputFile);

    // // Lê o arquivo até o final
    // while (1) {
        
    //     // Lê o primeiro número
    //     if (getline(&num1, &len1, inputFile) == -1) break;
    //     num1[strcspn(num1, "\n")] = '\0'; // Remove o '\n'

    //     // Lê o segundo número
    //     if (getline(&num2, &len2, inputFile) == -1) break;
    //     num2[strcspn(num2, "\n")] = '\0'; // Remove o '\n'

    //     // Lê o operador
    //     if (fscanf(inputFile, " %c\n", &operator) != 1) break;

    //     operacoes += 1;

    //     // Cria BigNumbers e insere os valores lidos
    //     A = bignumber();
    //     B = bignumber();
    //     C = bignumber();

    //     bignumber_insert_string(A, num1);
    //     bignumber_insert_string(B, num2);

    //     // Realiza o cálculo com base no operador
    //     if (operator == '+') {
    //         C = bignumber_add(A, B);
    //     } else {
    //         printf("Operador '%c' não suportado!\n", operator);
    //         continue;
    //     }

    //     bignumber_print(C);

    //     free(A);
    //     free(B);
    //     free(C);
    //     // printf("\n");
        
    // }

    // printf("%d", operacoes);
    // Fecha o arquivo
    

    // // Libera memória
    // bignumber_free(A);
    // bignumber_free(B);
    // bignumber_free(C);

//     return 0;
// }
