#ifndef ERRORS 
#include "errors.h"
#define ERRORS
#endif
#include "process.h"
#include "files.h"


#define CMD_ARG_INPUT_FILE_TOKEN 		"-in"
#define CMD_ARG_OUTPUT_FILE_TOKEN 			"-out"
#define CMD_ARG_OUTPUT_FMT_TOKEN				"-fmt"
#define CMD_ARG_FMT_CSV						"csv"
#define CMD_ARG_FMT_XML							"xml"
#define MAX_CMD_ARG					7

status_t validate_arguments(int argc, char *argv[], char **path_fi, char **path_fo, format_t * fmt);
