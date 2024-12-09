#ifndef ENVIR
#define ENVIR

void set_env_var(const char *key, const char *value);
void unset_env_var(const char *key);
char *get_env_var(const char *key);

#endif // ENVIR
