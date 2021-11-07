#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strings.h"

status_t split(const char *s, char delimitter, size_t *fields, char ***values)
{
	char *clone, *p , *q;
	size_t i;
	char tokens[2];
	
	if(s == NULL || fields == NULL || values == NULL)
	return ERROR_NULL_POINTER;
	
	tokens[0]=delimitter;
	tokens[1]='\0';
	
	if ((clone = strdup(s)) == NULL) 
	{
		*fields = 0;
		return ERROR_MEMORY;
	}
  
	for(i=0, (*fields)=0 ; (clone[i]) ; i++)
	{
		if(clone[i] == delimitter)(*fields)++;
	}
			
	(*fields)++;
	
	if(((*values)=(char**)malloc(sizeof(char*)*(*fields)))==NULL)
	{
		(*fields)=0;
		return ERROR_MEMORY;
	}

	for(i=0 , q=clone ; (p = strtok(q,tokens)) ; q=NULL , i++)
	{
		if(((*values)[i]=strdup(p))==NULL)
		{
			str_delete(values,i);
			free(clone);
			return ERROR_MEMORY;
		}
	}
	free(clone);
	return OK;
}

status_t str_delete(char ***values,size_t n)
{
	size_t i;
	
	if(values==NULL)return ERROR_NULL_POINTER;
	
	for (i=0 ; i< n ; i++)
	{
		free((*values)[i]);
		(*values)[i]=NULL;
	}
	free(*values);
	(*values)=NULL;
	return OK;
}

char *strdup (const char *cadena)
{
	char *clone;

	if((clone=(char*)malloc(strlen(cadena)+1))==NULL)
		return NULL;

	strcpy(clone, cadena);
		return clone;
}
