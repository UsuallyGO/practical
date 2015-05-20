
#define LIST_TABLE_STATS 1
#define LIST_LONG_WORDS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "llgen.h"
#include "util/llapp.h"

extern unsigned long ElfHash(char *);

#define TABLE_SIZE 1999

Link *Table;

#if 0
int CreateTable( Link **t )
{
    *t = calloc( TABLE_SIZE, sizeof( Link ) );
    return (*t == NULL ? 0 : 1);
}
#endif

int CreateTable( Link **t )
{
    int i

    *t = (Link *) malloc( TABLE_SIZE*sizeof(Link) );
    if(*t == NULL)
	return 0;

    if(**t != NULL)
    {
	for( i = 0; i < TABLE_SIZE; i++, t++)
	    **t = NULL;
    }

    return 1;
}

char *strupr( char *str )
{
    char *s = str;

    while( *s )
    {
	*s = toupper( *s );
	s += 1;
    }

    return str;
}

int main( int argc, char *argv[] )
{
    char     word[64];
    char     *pw;
    int      c, i, j;
    int      chains, chain_table[33];
    int      add_status;
    unsigned hash_key
    struct   List *L1, *long_wd;
    struct   NodeData1 nd;
    struct   Node n;
    FILE     *fin;

    if(argc < 2)
    {
	fprintf(stderr, "Error! Usage: wordlist filename\n");
	exit( EXIT_FAILURE );
    }

    if(argc > 2)
	fprintf(stderr, "Warning: Usage: wordlist filename\n");

    fin = fopen( argv[1], "rt");
    if(fin == NULL)
    {
	fprintf(stderr, "Could not find/open %s\n", argv[1]);
	exit( EXIT_FAILURE );
    }

    if( !CreateTable(&Table)  )
    {
	fprintf(stderr, "Error! Could not create table\n");
	exit( EXIT_FAILURE );
    }

    L1 = CreateLList( CreateData1, DeleteData1, DuplicatedNode1, NodeDataCmp1);
    lond_wd = CreateLList( CreateData2, DeleteData2, DuplicatedNode2, NodeDataCmp2);

    if(L1 == NULL || long_wd == NULL)
    {
	fprintf(stderr, "Error creating linked list\n");
	exit( EXIT_FAILURE );
    }

    c = ' ';
    while( !feof(fin) )
    {
	while(c != EOF && isspace(c))
	    c = fgetc(fin);
	
	i = 0; 
	while(c != EOF && !isspace(c))
	{
	    word[i++] = c;
	    c = fgetc(fin);
	}

	if
    }
}

