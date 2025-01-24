# Variables
CC = gcc # Compilator
CFLAGS = -std=c99 -Wall -Wextra -Wvla -g # Options to compile
OBJ = client.o bignumber.o line.o # Intermediate objects
TARGET = program # Executable name

# Rule to Compile all the program
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile client.o
client.o: client.c bignumber.h line.h
	$(CC) $(CFLAGS) -g -c client.c

# Compile bignumber.o
bignumber.o: bignumber.c bignumber.h
	$(CC) $(CFLAGS) -g -c bignumber.c

# Compile line.o
line.o: line.c line.h
	$(CC) $(CFLAGS) -g -c line.c
    
# clean the files
clean:
	rm -f $(OBJ) $(TARGET)