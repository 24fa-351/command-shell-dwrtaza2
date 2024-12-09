#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "envir.h"

// Substitute environment variables like $VAR
char *substitute_variables(char *input) {
    static char buffer[1024];
    char *buf_ptr = buffer;
    char *ptr = input;

    while (*ptr) {
        if (*ptr == '$') {
            ptr++;
            char var_name[128];
            int var_len = 0;

            while (isalnum(*ptr) || *ptr == '_') {
                var_name[var_len++] = *ptr++;
            }
            var_name[var_len] = '\0';

            char *value = get_env_var(var_name);
            if (value) {
                while (*value) *buf_ptr++ = *value++;
            }
        } else {
            *buf_ptr++ = *ptr++;
        }
    }

    *buf_ptr = '\0';
    return buffer;
}
