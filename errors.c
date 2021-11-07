#include <stdio.h>
#include "errors.h"

status_t show_error(status_t st)
{
	char * errors[MAX_ERRORS];
	
	errors[ ERROR_PROGRAM_INVOCATION ] = USR_MSG_ERROR_PROGRAM_INVOCATION;
		
	errors[ ERROR_NULL_POINTER ] = USR_MSG_ERROR_NULL_POINTER;

	errors[ ERROR_OPENING_INPUT_FILE ] = USR_MSG_ERROR_OPENING_INPUT_FILE;
	
	errors[ ERROR_OPENING_OUTPUT_FILE] = USR_MSG_ERROR_OPENING_OUTPUT_FILE;
	
	errors[ ERROR_DISK_SPACE] = USR_MSG_ERROR_DISK_SPACE;
		
	errors[ ERROR_MEMORY ] = USR_MSG_ERROR_MEMORY;
		
	errors[ ERROR_CORRUPT_FILE] = USR_MSG_ERROR_CORRUPT_FILE;
	
	
	fprintf(stderr,"%s\n",errors[st]);
	return OK;
}
