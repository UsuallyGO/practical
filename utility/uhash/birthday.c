
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 366

FILE *fin;
int  NameCount, DupeCount;

int hash_birthday( char* );

#ifdef __STDC__
//char* strdup( const char* );
#endif

int main( int argc, char* argv[] )
{
    char buffer[128];
    int  hash_value;
    char *name;
    char *Table[TABLE_SIZE];
    int  i;

    if(argc < 2)
    {
	fprintf(stderr, "Error! Expecting birthday file\n");
	exit( EXIT_FAILURE );
    }

    if((fin=fopen(argv[1], "rt")) == NULL)
    {
	fprintf(stderr, "Error! Cannot open %s\n", argv[1]);
	exit( EXIT_FAILURE );
    }

    for(i = 0; i < TABLE_SIZE; i++)
	Table[i] = NULL;

    while( !feof(fin) )
    {
	if(fgets(buffer, 128, fin) == NULL)
	    break;
	
	buffer[strlen(buffer)-1] = '\0';
	NameCount += 1;

	hash_value = hash_birthday(buffer);
	name = strdup(buffer + 4);

	if(Table[hash_value] == NULL)
	{
	    Table[hash_value] = name;
	    continue;
	}
	else
	{
	    DupeCount += 1;
	    printf("%s and %s have the same birthday.\n", name, Table[hash_value]);
	    continue;
	}
    }

    if(DupeCount == 0)
    {
	printf("No duplicate matches found among %d people.\n", NameCount);
	if(NameCount > 50)
	    printf("How rare!\n");
    }
    else
	printf("Among %d people, %d matches were found\n", NameCount, DupeCount);
	
    return EXIT_SUCCESS;
}

int hash_birthday( char *data )
{
    const int days_elapsed[12] = {   0,  31,  60,  91, 121, 152,
				   182, 213, 244, 274, 405, 335};
    int mm, dd;
    char record[128];

    strcpy(record, data);

    record[4] = '\0';
    dd = atoi(record + 2);
    record[2] = '\0';
    mm = atoi(record);

    if(mm < 1 || mm > 12)
    {
	fprintf(stderr, "Error in record for %s: %02d/%02d\n",
		(char*)data+4, mm, dd);
	exit( EXIT_FAILURE );
    }

    return (days_elapsed[mm-1] + dd);
}
