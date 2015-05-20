
#include <stdlib.h>
#include <string.h>

#define IN_LL_LIB 1

#include "llgen.h"

#define LLHead (L->LHead)
#define LLTail (L->LTail)
#define NodeCount (L->LCount)

#define CreateData    (*(L->LCreateData) )
#define DeleteData    (*(L->LDeleteData) )
#define DuplicateNode (*(L->LDuplicatedNode) )
#define NodeDataCmp   (*(L->LNodeDataCmp) )

int AddNodeAtHead( struct List* L, void* nd)
{
    Link pn;

    pn = CreateNode( L, nd );
    if(pn == NULL)
	return 0;

    if(LLHead == NULL)
	LLHead = LLTail = pn;
    else
    {
	LLHead->prev = pn;
	pn->next= LLHead;
	LLHead = pn;
    }

    NodeCount += 1;
    return 1;
}

int AddNodeAscend( struct List* L, void* nd )
{
    Link   pn;
    Link   prev, curr;
    struct Node dummy;
    int    compare;

    pn = CreateNode( L, nd );
    if(pn == NULL)
	return 0;

    dummy.next = LLHead;
    dummy.prev = NULL;
    if(dummy.next != NULL)
	dummy.next->prev = &dummy;

    prev = &dummy;
    curr = prev->next;
    for(; curr != NULL; prev = curr, curr = curr->next)
    {
	compare = NodeDataCmp( pn->pdata, curr->pdata );
	if(compare <= 0)
	    break; //should be here before curr
    }

    if(curr != NULL && compare == 0)
    {
	compare = DuplicateNode( pn, curr );
	if(compare == 2)
	   ; /* do nothing here */
	else
	{
	    LLHead = dummy.next;
	    LLHead->prev = NULL;

	    if(compare == 1)
	    {
		DeleteData( pn->pdata );
		free( pn );
	    }
	    return 1;
	}
    }

    prev->next = pn;
    pn->prev = prev;
    pn->next =curr;
    if(curr != NULL)
	curr->prev = pn;
    else
	LLTail = pn;

    NodeCount += 1;

    LLHead = dummy.next;
    LLHead->prev = NULL;
    return 1;
}

struct List* CreateLList(
	    void* (* fCreateData )     ( void* ),
	    int   (* fDeleteData )     ( void* ),
	    int   (* fDuplicatedNode ) ( Link, Link ),
	    int   (* fNodeDataCmp )    ( void*, void* ))
{
    struct List* pL;

    pL = (struct List*)malloc(sizeof(struct List));
    if(pL == NULL)
	return NULL;
    pL->LHead = NULL;
    pL->LTail = NULL;
    pL->LCount = 0;

    pL->LCreateData = fCreateData;
    pL->LDeleteData = fDeleteData;
    pL->LDuplicatedNode = fDuplicatedNode;
    pL->LNodeDataCmp = fNodeDataCmp;

    return pL;
}

Link CreateNode( struct List* L, void* data )
{
    Link new_node;

    new_node = (Link)malloc(sizeof(struct Node));
    if(new_node == NULL)
	return NULL;

    new_node->prev = NULL;
    new_node->next = NULL;

    new_node->pdata = CreateData( data );
    if(new_node->pdata == NULL)
    {
	free( new_node );
	return NULL;
    }
    else
	return new_node;
}

int DeleteNode( struct List* L, Link to_delete )
{
    Link pn;
    if(to_delete == NULL)
	return 0;

    if(to_delete->prev == NULL)
    {
	LLHead = to_delete->next;
	LLHead->prev = NULL;
    }
    else if(to_delete->next == NULL)
    {
	LLTail = to_delete->prev;
	LLTail->next = NULL;
    }
    else
    {
	pn = to_delete->prev;
	pn->next = to_delete->next;

	pn = to_delete->next;
	pn->prev = to_delete->prev;
    }

    DeleteData( to_delete->pdata );
    free( to_delete );

    NodeCount -= 1;
    return 1;
}

Link FindNode( struct List* L, void* nd )
{
    Link pcurr;

    if(LLHead == NULL)
	return NULL;

    for(pcurr = LLHead; pcurr != NULL; pcurr = pcurr->next)
    {
	if(NodeDataCmp(nd, pcurr->pdata ) == 0)
	    return pcurr;
    }

    return NULL;
}

Link FindNodeAscend( struct List* L, void *nd )
{
    Link pcurr;
    int  cmp_result;

    if(LLHead == NULL)
	return NULL;

    for(pcurr = LLHead; pcurr != NULL; pcurr = pcurr->next)
    {
	cmp_result = NodeDataCmp( nd, pcurr->pdata );
	if(cmp_result < 0)
	    return NULL;
	else if(cmp_result == 0)
	    return pcurr;
    }

    return NULL;
}
