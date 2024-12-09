#include "core_commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void handle_builtin(char **args) {
  if (strcmp(args[0], "cd") == 0) {
    if (args[1]) {
      if (chdir(args[1]) < 0) {
        perror("cd");
      }
    } else {
      fprintf(stderr, "Usage: cd <directory>\n");
    }
  } else if (strcmp(args[0], "pwd") == 0) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd))) {
      printf("%s\n", cwd);
    } else {
      perror("pwd");
    }
  } else if (strcmp(args[0], "set") == 0) {
    if (args[1] && args[2]) {
      set_env_var(args[1], args[2]);
    } else {
      fprintf(stderr, "Usage: set <key> <value>\n");
    }
  } else if (strcmp(args[0], "unset") == 0) {
    if (args[1]) {
      unset_env_var(args[1]);
    } else {
      fprintf(stderr, "Usage: unset <key>\n");
    }
  }
}