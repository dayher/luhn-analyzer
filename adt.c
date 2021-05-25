#include "adt.h"

#include <stdio.h>

status_t ADT_List_new (ADT_List_t * pl)
{
	if (pl == NULL)
		return ERROR_NULL_POINTER;
	*pl = NULL;
	return OK;
}

status_t ADT_List_create_node (const void * pd, list_node_t ** pn)
{

	if (pd == NULL || pn == NULL)
		return ERROR_NULL_POINTER;
		
	if ((*pn = (list_node_t *) malloc(sizeof(list_node_t))) == NULL)
		return ERROR_MEMORY;
	(*pn)->data = pd;
	(*pn)->next = NULL;
	return OK;
}

status_t ADT_List_insert (ADT_List_t * pl, const void * what)
{	
	struct list_node_t * pn;
	status_t st;
	
	if (pl == NULL || what == NULL)
		return ERROR_NULL_POINTER;

	if ((st = ADT_List_create_node(what,&pn)) != OK)
		return st;

	pn->next = *pl;
	*pl = pn;
	return OK;
}

status_t ADT_List_add (ADT_List_t * pl , ADT_List_t * prev, void const * what)
{
	list_node_t * pn;
	status_t st;
	
	if (pl == NULL || prev == NULL || what == NULL)
		return ERROR_NULL_POINTER;

	if ((st = ADT_List_create_node(what,&pn)) != OK)
		return st;

	pn->next = *pl;
	(*prev)->next = pn;
	return OK;
}

status_t ADT_List_append (ADT_List_t * pl, const void * what)
{
	struct list_node_t * pn;
	status_t st;

	if (pl == NULL || what == NULL)
		return ERROR_NULL_POINTER;
		
	if ((st = ADT_List_create_node(what,&pn)) != OK)
		return st;
		
	(*pl)->next = pn;
	
	return OK;
}

status_t ADT_List_destroy (ADT_List_t * L, destructor_t destructor )
{
	status_t st;
	list_node_t * pn, *temp;
	
	if( L==NULL || destructor==NULL) return ERROR_NULL_POINTER;
	
	pn = ((list_node_t *)(*L)->data);
	
	while(pn)
	
	{
		temp = pn->next;
		
		if ( (st = ADT_List_destroy_node (&pn, destructor) ) != OK ) return st;
		
		pn = temp;	
	}
	free(*L);
	*L = NULL;
	return OK;
}

status_t ADT_List_destroy_node (list_node_t ** p, status_t (*pf)(const void *))
{
	status_t st;

	if (p == NULL || pf == NULL) return ERROR_NULL_POINTER;
	if ((st = (*pf)((*p)->data)) != OK)
		return st;
	(*p)->data = NULL;
	free(*p);	
	*p = NULL;
	return OK;
}

status_t destroy_transactions(ADT_List_t * SL)
{
	status_t st;
	list_node_t * pn, *temp;
	
	if( SL==NULL ) return ERROR_NULL_POINTER;
	
	pn = (*SL);
	
	while(pn)
	{
		temp = pn->next;
		if ( (st = ADT_List_destroy (&pn, &ADT_Transaction_destroy) ) != OK ) return st;
		pn = temp;	
	}
	
	*SL = NULL;
	return OK;
}

status_t ADT_Transaction_destroy(const void * record)
{
	
	if( record==NULL ) return ERROR_NULL_POINTER;
	
	free((ADT_Transaction_t)record);
	record=NULL;
	return OK;
}

status_t ADT_List_traverse (ADT_List_t TL, printer_t printer,char context, FILE * fo)
{
	status_t st;
	
	if(TL==NULL || fo==NULL || printer==NULL) return ERROR_NULL_POINTER;

	while (TL)
	{
 		if ((st = (*printer)((ADT_Transaction_t)(TL->data), context, fo)) != OK)
			return st;
		TL = TL->next;
	}
	return OK;
}
