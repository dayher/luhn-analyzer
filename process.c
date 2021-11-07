#include "process.h"

status_t process_records(FILE *fi,FILE *fo, format_t fmt)
{
	status_t st;
	ADT_Transaction_t  record;
	ADT_List_t SL, TL;
	
	if( (st = load_transaction(fi,&record)) != OK) return st;	

	if( (st = ADT_List_new (&TL)) != OK) return st;

	if( (st = ADT_List_new (&SL)) != OK) return st;

	if( (st = ADT_List_insert(&TL, record)) != OK) return st;

	if( (st = ADT_List_insert(&SL, TL)) != OK) return st;
	
	while(!feof(fi))
	{
	
		if((st = load_transaction(fi,&record)) != OK  ){	
		 	destroy_transactions(&SL);
		 	return st;
		}
		
		if(feof(fi)) break;
	
		if((st = sort_incresing_store(&SL, record)) != OK) {	
	 		destroy_transactions(&SL);
	 		return st;
		}
	}
	 
	if((st= print_transactions(SL, fmt, CONTEXT, fo))!=OK) return st;
	
	return destroy_transactions(&SL);
}


status_t sort_incresing_store (ADT_List_t * SL, ADT_Transaction_t  record)
{	
	list_node_t *TL, *store = *SL, *prev_store = NULL;
	uint current_store_id = ((ADT_Transaction_t)(((ADT_List_t)(store->data))->data))->store_id;
	status_t st;
	
	if (SL == NULL || record == NULL)	return ERROR_NULL_POINTER;
	
	while(store)
	{
		if(record->store_id > current_store_id ) 
		{
 			if(!store->next)
 			{
 				if( (st = ADT_List_new (&TL)) != OK) return st;
				if( (st = ADT_List_insert(&TL, record)) != OK) return st;
 				return ADT_List_append(&store,TL);
 			}
  			prev_store = store ; 
  			store = store->next;
		} 
		else if (record->store_id < current_store_id )
		{  
			if( (st = ADT_List_new (&TL)) != OK) return st;
			if( (st = ADT_List_insert(&TL, record)) != OK) return st;
			if(!prev_store) return ADT_List_insert(SL, TL);
  			return ADT_List_add(&store, &prev_store, TL);	
		}
		else return  sort_decresing_value(&store ,record);		
	}
	return OK;	
}

status_t sort_decresing_value(ADT_List_t * TL , ADT_Transaction_t  record)
{
  	list_node_t * transaction = ((list_node_t *)(*TL)->data), *prev_transaction = NULL;
	
	if (TL == NULL || record == NULL)	return ERROR_NULL_POINTER;

	while(transaction)
	{
		if(record->value <= ((ADT_Transaction_t)(transaction->data))-> value) 
		{
			if(!transaction->next) return ADT_List_append(&transaction, record);
         		 prev_transaction = transaction ;
         		 transaction = transaction->next;
		} 
      		else
      		{  
        		if(!prev_transaction)  return ADT_List_insert(TL, record) ; 
          		return ADT_List_add(&transaction, &prev_transaction, record);
		}
	}
}
