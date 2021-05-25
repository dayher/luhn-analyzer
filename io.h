#include "strings.h"

#ifndef ADT
#include "adt.h"
#define ADT
#endif

#ifndef ERRORS
#include "errors.h"
#define ERRORS
#endif

#define TOKEN_RECORD_ID		0
#define TOKEN_RECORD_VALUE		3
#define TOKEN_RECORD_STORE_ID		2
#define TOKEN_RECORD_CARD_NUMBER	1
#define MAX_TOKENS_RECORD		5
#define MAX_CREDIT_CARD_NUMBERS 	16
#define MAX_LINE			100
#define CONTEXT 			'|'
#define DELIMMITER			','
#define BASE 				10


typedef unsigned int uint;
typedef enum {CSV,XML} format_t;
typedef enum {TRUE,FALSE} bool_t;

status_t load_transaction(FILE * fi, ADT_Transaction_t * record);

status_t read_record(FILE * fi,  char ***arr);

bool_t validate_card_number(char ** s);

status_t set_transaction (char ***s, ADT_Transaction_t * record);

status_t print_transactions(ADT_List_t SL,format_t fmt ,char context,FILE * fo);

status_t ADT_Transaction_printer_csv(ADT_Transaction_t record, char context, FILE *fo);

status_t ADT_Transaction_printer_xml(ADT_Transaction_t record, char context, FILE *fo);
