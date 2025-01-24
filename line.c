#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief function to read a line that the size varies
 */
char *read_line(void) {
    char *line = NULL;
    size_t len = 0;
    size_t read;

    read = getline(&line, &len, stdin);
    if (read == -1) {
        free(line);
        return NULL;
    }

    // Remove o \n do final da linha
    if (line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }

    return line;
}
