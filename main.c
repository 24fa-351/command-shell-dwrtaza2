#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core_commands.h"
#include "execute.h"
#include "envir.h"

#define INPUT_BUFFER 1024

int main() {
    char input[1024];

    printf("Welcome to xsh! Type 'exit' or 'quit' to exit.\n");
    while (1) {
        printf("xsh# ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;

        input[strcspn(input, "\n")] = '\0'; // Remove newline
        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) break;

        execute_command(input);
    }

    return 0;
}