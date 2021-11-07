#include <stdio.h>
#include "files.h"


status_t open_files(FILE **fi, FILE **fo, char *path_fi, char *path_fo)
{
	if(((*fi)=fopen(path_fi,"rt"))==NULL)
	{
		return ERROR_OPENING_INPUT_FILE;
	}
				
	if(((*fo)=fopen(path_fo,"wt"))==NULL)
	{
		return ERROR_OPENING_OUTPUT_FILE;
	}
	return OK;
}

status_t close_files(FILE **fi, FILE **fo)
{
	fclose((*fi));
	if(fclose((*fo))==EOF)
	{
		show_error(ERROR_DISK_SPACE);
		return ERROR_DISK_SPACE;
	}
	return OK;
}
