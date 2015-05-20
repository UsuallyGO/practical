
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llgen.h"
#include "util/llapp.h"

int main( int argc, char* argv[] )
{
    char   word[64];
    int    count;
    struct List *L1, *L2;
    Link   w1, w2, w3;

    FILE   *fin;

/*
    if(argc != 2)
    {
	fprintf(stderr, "Error! Usage: lldriver filename\n");
	exit(EXIT_FAILURE);
    }
*/

    //fin = fopen( argv[1], "rt" );
    fin = fopen( "temp.txt" ,"rt" );
    if(fin == NULL)
    {
	fprintf(stderr, "Could not find/open %s\n", argv[1]);
	exit(EXIT_FAILURE);
    }

    L1 = CreateLList( CreateData1, DeleteData1, DuplicatedNode1, NodeDataCmp1 );
    L2 = CreateLList( CreateData2, DeleteData2, DuplicatedNode2, NodeDataCmp2 );

    if(L1 == NULL || L2 == NULL)
    {
	fprintf(stderr, "Error creating linked list\n");
	exit(EXIT_FAILURE);
    }

    while(fgets(word, 64, fin) != NULL)
    {
	if(strlen(word) > 0)
	    word[strlen(word)-1] = 0;
	if( !AddNodeAscend(L1, word) )
	    fprintf(stderr, "Warning! Error whle adding node to L1.\n");
	if( !AddNodeAscend(L2, word) )
	    fprintf(stderr, "Warning! Error whle adding node to L2.\n");
    }
    fclose(fin);
	
    printf("L1 contains %u items:\n", L1->LCount);
    for(w1 = L1->LHead; w1 != NULL; w1=w1->next)
	printf("    %s occured %d times.\n", ((pND1)(w1->pdata))->word, ((pND1)(w1->pdata))->u);

    printf("L2 contains %u items:\n", L2->LCount);
    for(w1 = L2->LHead; w1 != NULL; w1=w1->next)
	printf("    %s\n", ((pND2)(w1->pdata))->word);

    w1 = L2->LHead;
    w2 = L2->LTail;
    for( ; w1 != NULL && w2 != NULL; w1=w1->next, w2=w2->prev)
	printf("    %30s    %30s\n", ((pND2)(w1->pdata))->word, ((pND2)(w2->pdata))->word);

    count = 0;
    w1 = L2->LHead;
    while(w1 != NULL)
    {
	w3 = FindNode(L2, w1->pdata);
	if(w3 != 0)
	{
	    printf("Found node %s", ((pND2)(w3->pdata))->word);
	    count += 1;
	    w1 = w3->next;
	    if(count & 1)
	    {
		DeleteNode( L2, w3 );
		printf("    and deleted it.");
	    }
	    printf("\n");
	}
	else
	    w1 = NULL;
    }
	
    printf("L2 contains %u items:\n", L2->LCount);
    w1 = L2->LHead;
    w2 = L2->LTail;
    for( ; w1 != NULL && w2 != NULL; w1=w1->next, w2=w2->next)
	printf("	%30s %30s\n", ((pND2)(w1->pdata))->word,	    
				      ((pND2)(w1->pdata))->word);

    return EXIT_SUCCESS;
}
