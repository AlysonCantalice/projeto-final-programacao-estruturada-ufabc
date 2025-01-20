#include <stdio.h>
#include "bignumber.h"

// ENTRADAS E SAÍDAS:
// A entrada para o seu programa é fornecida via a entrada padrão (teclado do usuário) e o seu programa
// deve fornecer a saída na saída padrão (escrever na tela).

// VAZAMENTO DE MEMÓRIA PARA SOMA E SUBTRAÇÃO ESTÁ OK.
// valgrind --leak-check=yes ./program ./tests/instances/04_small_pos_minus.in

// para rodar com gdb: (para funcionar, precisa alterar read_file() para: argc != 1 e fopen(argv[0])) 
// gdb ./program
// run < teste.txt

// TESTE 1 AO 9 PASSOU. O 10 DEU ERRO!
// $ rm out.txt 
// $ ./program < ./tests/instances/10_small_minus.in >> out.txt
// $ diff out.txt ./tests/instances/10_small_minus.out  

// -----------------------------------------
// Iniciar a instância de calculadora de BigNumber
 
int main(){

    bignumber_calculator();

    return 0;
}


// -----------------------------------------
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


// ------------------------------------------
// usando o input como inteiro

// int main(){
//     int num1, num2;
//     char operator;
//     BigNumber *A, *B, *C;
    
//     // Cria BigNumbers e insere os valores lidos
//     A = bignumber();
//     B = bignumber();
//     C = bignumber();

//     bignumber_insert(A, num1);
//     bignumber_insert(B, num2);

//     C = operation_realized(operator, A, B, C);

//     bignumber_print(C);

//     bignumber_free(A);
//     bignumber_free(B);
//     bignumber_free(C);

//     return 0;    
// }
