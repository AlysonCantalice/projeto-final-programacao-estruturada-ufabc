# Variáveis
CC = gcc # Compilador
CFLAGS = -std=c99 -Wall -Wextra -Wvla -g # Opções de compilação
OBJ = client.o bignumber.o # Objetos intermediários
TARGET = program # Nome do executável

# Regra padrão para compilar o programa
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compilar client.o
client.o: client.c bignumber.h
	$(CC) $(CFLAGS) -c client.c

# Compilar bignumber.o
bignumber.o: bignumber.c bignumber.h
	$(CC) $(CFLAGS) -c bignumber.c

# Limpeza de arquivos gerados
clean:
	rm -f $(OBJ) $(TARGET)
