#include <stdio.h>
#include <stdlib.h>
#include "io.h"

status_t read_record(FILE * fi,  char ***arr)
{
	char line[MAX_LINE+2];

	size_t len;
	status_t st;
  
		
	if(fi==NULL || arr==NULL) return ERROR_NULL_POINTER;
	
	if(fgets(line, MAX_LINE+2 ,fi) != NULL)
	{
		
		if( (st = split(line,DELIMMITER,&len,arr)) != OK) 
			return st;
		
		if(len!=MAX_TOKENS_RECORD) 
			return ERROR_CORRUPT_FILE;			
	}
	return OK;
}

status_t load_transaction(FILE * fi, ADT_Transaction_t * record)
{
	status_t st;
  	char **s;
  	
  	if(fi==NULL || record==NULL) return ERROR_NULL_POINTER;
  	
	if((st = read_record(fi,&s))!=OK) return st;
	
	if(feof(fi)) return OK;

	while( (validate_card_number(&s[TOKEN_RECORD_CARD_NUMBER])==TRUE) &&(!feof(fi)))

	{
		if((st = read_record(fi,&s))!=OK) return st;
	}
	
	if((st=set_transaction(&s,record))!=OK) return st;
	
	return OK;

}

status_t set_transaction (char ***s, ADT_Transaction_t * record)
{

	char *temp_id, *temp_store_id, *temp_value;
	
	if(s == NULL || record == NULL) return ERROR_NULL_POINTER;
	
	if((*record = (ADT_Transaction_t)malloc(sizeof(transaction_t))) == NULL) return ERROR_MEMORY;

	(*record) -> id = (uint)strtol((*s)[TOKEN_RECORD_ID],&temp_id,BASE);
	(*record) -> value = (float)strtod((*s)[TOKEN_RECORD_VALUE],&temp_value);
	(*record) -> store_id = (uint)strtol((*s)[TOKEN_RECORD_STORE_ID],&temp_store_id,BASE);

	str_delete(s,MAX_TOKENS_RECORD);

	if ( (*temp_id && *temp_id != '\n') || (*temp_value && *temp_value != '\n') || (*temp_store_id && *temp_store_id != '\n') )
		return ERROR_CORRUPT_FILE;
		
  return OK;
}

bool_t validate_card_number(char ** s)
{
       
	int a;
	size_t valor, i;

	for (i=1,valor=0;i<=MAX_CREDIT_CARD_NUMBERS;i++){
	    a= s[1][i]-48;
	    
	  if(i%2){  
	    a*=2; 
	  }

	    if(a>9){
	      valor+=a-9;
	      continue;
	      
	    }

	  valor+=a;
	  }
	   
	  if (valor==80)
	    return TRUE;
	  else
	    return FALSE;
    
}

status_t print_transactions(ADT_List_t SL,format_t fmt, char context, FILE * fo)
{
  
	status_t st;

	if(SL==NULL || fo==NULL) return ERROR_NULL_POINTER;
 	
	if (fmt == CSV) {

		while(SL){
			if ( (st = ADT_List_traverse((ADT_List_t)(SL->data), ADT_Transaction_printer_csv, context,fo)) != OK) return st;
			SL= SL->next;
		}
	} 
	
	else if (fmt == XML) {
		fprintf(fo,"<?xml version=\"1.0\" ?>\n<transactions>\n");
		while(SL)
		{
			if ( (st = ADT_List_traverse((ADT_List_t)(SL->data), ADT_Transaction_printer_xml, context,fo)) != OK) return st;
			SL= SL->next;
		}
		fprintf(fo,"</<transactions>\n");
	}
	return OK;
}

status_t ADT_Transaction_printer_csv(ADT_Transaction_t  record, char context, FILE *fo)
{	
	fprintf(fo,"%u%c%d%c%.2f\n", record->store_id, context, record->id, context, record->value);
	return OK;
}

status_t ADT_Transaction_printer_xml(ADT_Transaction_t record, char context, FILE *fo)
{
	fprintf(fo,"\t<transaction>\n\t\t<store_id>%u</store_id>\n\t\t<transaction_id>%d</transaction_id>\n\t\t<amount>%.2f</amount>\n\t</transaction>\n", record->store_id, record->id, record->value);
	return OK;
}
