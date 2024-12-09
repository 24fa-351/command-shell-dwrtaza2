#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "execute.h"
#include "core_commands.h"
#include "envir.h"

void execute_command(char *input) {
    char *args[128];
    char *token;
    int background = 0;
    int pipe_fds[2];
    int input_fd = STDIN_FILENO, output_fd = STDOUT_FILENO;

    input = substitute_variables(input);  // Environment variable substitution

    // Tokenize input
    token = strtok(input, " ");
    int arg_count = 0;

    while (token) {
        if (strcmp(token, "&") == 0) {
            background = 1;
            break;
        } else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " ");
            input_fd = open(token, O_RDONLY);
            if (input_fd < 0) {
                perror("open");
                return;
            }
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " ");
            output_fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (output_fd < 0) {
                perror("open");
                return;
            }
        } else {
            args[arg_count++] = token;
        }
        token = strtok(NULL, " ");
    }
    args[arg_count] = NULL;

    pid_t pid = fork();
    if (pid == 0) { // Child process
        // Handle input redirection
        if (input_fd != STDIN_FILENO) {
            dup2(input_fd, STDIN_FILENO);  // Redirect input to file
            close(input_fd);  // Close original file descriptor
        }

        // Handle output redirection
        if (output_fd != STDOUT_FILENO) {
            dup2(output_fd, STDOUT_FILENO);  // Redirect output to file
            close(output_fd);  // Close original file descriptor
        }

        // Execute command
        execvp(args[0], args);
        perror("execvp");  // If exec fails
        exit(1);
    } else if (pid > 0) { // Parent process
        if (!background) {
            waitpid(pid, NULL, 0);  // Wait for child process to finish
        }
    } else {
        perror("fork");
    }
}