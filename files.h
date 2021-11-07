#ifndef ERRORS 
#include "errors.h"
#define ERRORS
#endif
status_t open_files(FILE **fi, FILE **fo, char *path_fi, char *path_fo);
status_t close_files(FILE **fi, FILE **fo);
