#include <stdio.h>


int main() {

    long long a = 319; // Dividendo
    int b = 3;                   // Divisor
    long long c = 0;              // Resultado da divisão
    long long d = 0;              // Valor auxiliar para multiplicar
    long long e = 0;              // Valor auxiliar (resto)

    while (a >= b) {
        long long potencia = 1;
        long long temp = b;

        // Determinar a maior potência de 10 para multiplicar b sem ultrapassar a
        while (temp * 10 <= a) {
            temp *= 10;
            potencia *= 10;
        }

        // Determinar o valor do dígito mais significativo do quociente
        int digito = 1;
        while ((digito + 1) * temp <= a) {
            digito++;
        }

        // Atualizar os valores de c, d e a
        c = c * 10 + digito;
        d = temp * digito;  
        a -= d;
    }

    e = a; // O que sobra em "a" é o resto

    printf("Resultado da divisão (c): %lld\n", c);
    printf("Resto da divisão (e): %lld\n", e);

    return 0;
}
