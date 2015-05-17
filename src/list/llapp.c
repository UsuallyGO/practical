
#include <stdlib.h>
#include <string.h>

#include "llgen.h"
#include "src/llapp.h"

void* CreateData1( void* data )
{
    struct NodeData1* new_data;

    new_data = (struct NodeData1*)malloc(sizeof(struct NodeData1));
    if(new_data == NULL)
	return NULL;

    new_data->u = 1;
    new_data->word = strdup( (char*)data );
    if(new_data->word == NULL)
    {
	free(new_data);
	return NULL;
    }
    else
	return new_data;
}

int DeleteData1( void* data )
{
    free(((pND1)data)->word);
    return 1;
}

int DuplicatedNode1( Link new_node, Link list_node )
{
    pND1 pnd = list_node->pdata;
    pnd->u += 1;
    return 1;
}

int NodeDataCmp1( void *first, void *second )
{
    return strcmp( ((pND1)first)->word, ((pND1)second)->word );    
}

void* CreateData2( void *data )
{
    struct NodeData2 *new_data;

    new_data = (pND2)malloc(sizeof(struct NodeData2));
    new_data->word = strdup((char*)data);
    if(new_data->word == NULL)
    {
	free(new_data);
	return NULL;
    }
    else
	return new_data;
}

int DeleteData2( void *data )
{
    free( ((pND2)data)->word );
    return 1;
}

int DuplicatedNode2( Link new_node, Link list_node )
{
    return 2;
}

int NodeDataCmp2( void *first, void *second )
{
    return strcmp( ((pND2)first)->word, ((pND2)second)->word );
}
