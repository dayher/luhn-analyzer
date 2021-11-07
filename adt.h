#include <stdlib.h>
#include <stdio.h>

#ifndef ERRORS
#include "errors.h"
#define ERRORS
#endif

typedef struct list_node_t
{
	const void * data;
	struct list_node_t * next;

} list_node_t, *ADT_List_t;

typedef struct  transaction_t
{
  uint id;
  uint store_id;
  float value;
  char * cc_num;

} transaction_t, *ADT_Transaction_t;

typedef status_t (*destructor_t)(const void *);
typedef status_t (*printer_t)(ADT_Transaction_t  record , char delimmter, FILE *fo);

status_t ADT_List_new (ADT_List_t *);
status_t ADT_List_create_node (const void *, list_node_t **);
status_t ADT_List_insert (ADT_List_t *, const void * what);
status_t ADT_List_add (ADT_List_t *, ADT_List_t *, const void * what);
status_t ADT_List_append (ADT_List_t *, const void * what);


status_t ADT_List_destroy (ADT_List_t *, destructor_t );
status_t ADT_List_destroy_node (list_node_t **, destructor_t);
status_t ADT_Transaction_destroy(const void * record);
status_t destroy_transactions(ADT_List_t *);

status_t ADT_List_traverse (ADT_List_t TL, printer_t, char, FILE *);



