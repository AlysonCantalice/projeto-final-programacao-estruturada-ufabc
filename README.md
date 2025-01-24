# Projeto - Biblioteca BigNumber

## INTRODUÇÃO

Este projeto tem como objetivo a implementação da estrutura BigNumber para realizar o armazenamento e cálculo de números inteiros muito grandes, onde a única limitação é a quantidade de memória da máquina que executa o programa. Foram implementadas as operações aritméticas básicas, como soma, subtração, multiplicação, divisão e resto da divisão de números grandes.

## SOBRE O CÓDIGO

O código foi estruturado de forma modular seguindo as diretrizes do projeto, dividindo o uso e implementação da estrutura BigNumber em diferentes arquivos, sendo eles:

- big_number.c: Implementação principal da estrutura BigNumber. Contém as funções aritméticas principais, além de funções privadas auxiliares da biblioteca.
- big_number.h: interface pública da biblioteca
- line.c: Implementação de leitura de linha.
- line.h: interface pública da biblioteca
- client.c: entrada principal do programa

Utilizamos o VSCode para escrever o código. Através da extensão¹ C/C++, configuramos a ferramenta de indentação (linter) no padrão LLVM² com uma customização para a largura da indentação ser 4 espaços (IndentWidth) e adotamos o padrão doxygen³ para comentários de funções a fim de manter boas práticas de software.

## FUNCIONALIDADES IMPLEMENTADAS

- Soma
- Subtração
- Multiplicação
- Divisão
- Resto de divisão

Para mais informações, verificar os comentários e descrições no código.

## INTERFACE PÚBLICA

- typedef struct Node {Struct Node *prev; int digit; struct Node *next;} Node;
- typedef struct {Node *head; Node *tail; int sign;} BigNumber;
- BigNumber \*bignumber(void);
- void bignumber_insert(BigNumber \*bn, int n);
- void bignumber_insert_string(BigNumber *bn, char *digit_string);
- BigNumber _operation_realized(char operator, BigNumber _ A, BigNumber *B, BigNumber *C);
- void bignumber_free(BigNumber \*bn);
- void bignumber_print(BigNumber \*bn);
- BigNumber *bignumber_add(BigNumber *A, BigNumber \*B);
- BigNumber *bignumber_subtract(BigNumber *A, BigNumber \*B);
- BigNumber *bignumber_multiplication(BigNumber *A, BigNumber \*B);
- BigNumber *bignumber_division(BigNumber *A, BigNumber \*B);
- BigNumber *bignumber_remainder(BigNumber *A, BigNumber \*B);
- char \*read_line(void);

## FUNÇÕES AUXILIARES

- bignumber_insert / bignumber_insert_string - Insere um dígito ou uma string de dígitos em um BigNumber.
- read_line - Ler uma linha do input
- operation_realized - Realiza uma determinada operação dependendo da entrada fornecida.
- bignumber_free - Libera a memória alocada de um BigNumber.
- bignumber_print - Printa o valor de um BigNumber.
- bignumber_reverse - Inverte um BigNumber.
- bignumber_remove_left_zeros - Remove os zeros a esquerda de um BigNumber. Ex: 00010 -> 10.
- bignumber_copy_value - Copia o valor de um BigNumber para outro.
- bignumber_compare - Compara dois BigNumbers e identifica o maior.
