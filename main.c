#include <stdio.h>
#include <string.h>
#include "main.h"

int main (int argc , char *argv[])
{	
	FILE *fi, *fo;
	char * path_fi, *path_fo;
	status_t st;
	format_t fmt;	
	
	if( (st=validate_arguments(argc, argv, &path_fi, &path_fo, &fmt)) != OK)
		return show_error(st);
	
	if( (st=open_files(&fi,&fo, path_fi, path_fo)) !=OK)
		return show_error(st);	
	
	if( (st=process_records(fi,fo,fmt)) != OK)
	{
		show_error(st);

		close_files(&fi,&fo);
			
		remove (path_fo);
		
		return st;
	}

	if( (st=close_files(&fi,&fo)) != OK)
		return show_error(st);	
	
	return OK;
}

status_t validate_arguments(int argc, char *argv[], char ** path_fi, char **path_fo, format_t * fmt)
{
	char *tmp;
	size_t i;
	int args_to_parse;

	if(path_fi == NULL || path_fo == NULL || fmt == NULL || argv == NULL)
		return ERROR_NULL_POINTER;
	

	if(argc != MAX_CMD_ARG) 
		return ERROR_PROGRAM_INVOCATION;
	

	for(i = 1, args_to_parse = MAX_CMD_ARG - 1; i < argc - 1; i += 2) 
	{
		if(!strcmp(argv[i], CMD_ARG_INPUT_FILE_TOKEN)) 
		{
			*path_fi = argv[i + 1];
			
			args_to_parse -= 2;
		}

		if(!strcmp(argv[i], CMD_ARG_OUTPUT_FILE_TOKEN)) 
		{
			*path_fo = argv[i + 1];
			
			args_to_parse-=2;
    		}
    		
    		if(!strcmp(argv[i], CMD_ARG_OUTPUT_FMT_TOKEN)) 
		{
			if(!strcmp(argv[i + 1] , CMD_ARG_FMT_CSV)) *fmt = CSV ;
			else if(!strcmp(argv[i + 1] , CMD_ARG_FMT_XML)) *fmt = XML ;
			else return ERROR_PROGRAM_INVOCATION;
			
			args_to_parse-=2;
    		}
	}

	if(args_to_parse != 0) 
		return ERROR_PROGRAM_INVOCATION;
	
 return OK;	
	
}  
