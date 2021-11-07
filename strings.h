#ifndef ERRORS
#include "errors.h"
#define ERRORS
#endif
status_t split(const char *s, char delimitter, size_t *fields, char ***values);
status_t str_delete(char ***values,size_t n);
char *strdup (const char *string);
