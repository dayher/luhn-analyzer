#include <stdio.h>
#include "io.h"

#ifndef ADT
#include "adt.h"
#define ADT
#endif

#ifndef ERRORS
#include "errors.h"
#define ERRORS
#endif

status_t process_records(FILE *fi,FILE *fo, format_t fmt);
status_t sort_incresing_store (ADT_List_t * SL, ADT_Transaction_t  record);
status_t sort_decresing_value(ADT_List_t * TL , ADT_Transaction_t  record);
