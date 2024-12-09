#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "envir.h"

#define MAX_ENV_VARS 100

typedef struct {
    char *key;
    char *value;
} EnvVar;

EnvVar env_vars[100];
int env_count = 0;

void set_env_var(const char *key, const char *value) {
    for (int i = 0; i < env_count; i++) {
        if (strcmp(env_vars[i].key, key) == 0) {
            free(env_vars[i].value);
            env_vars[i].value = strdup(value);
            return;
        }
    }
    env_vars[env_count].key = strdup(key);
    env_vars[env_count].value = strdup(value);
    env_count++;
}

void unset_env_var(const char *key) {
    for (int i = 0; i < env_count; i++) {
        if (strcmp(env_vars[i].key, key) == 0) {
            free(env_vars[i].key);
            free(env_vars[i].value);
            env_vars[i] = env_vars[--env_count];
            return;
        }
    }
}

char *get_env_var(const char *key) {
    for (int i = 0; i < env_count; i++) {
        if (strcmp(env_vars[i].key, key) == 0) {
            return env_vars[i].value;
        }
    }
    return NULL;
}