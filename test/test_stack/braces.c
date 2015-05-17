
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/stacks.h"

#define MAX 1000

int main( int argc, char *argv[] )
{
    FILE*  fin;
    char   buffer[MAX];
    int    line_count;
    struct StkElement *stk_el;
    Stack  *stk;
    char   ch;
    int    i;

    if(argc != 2)
    {
	fprintf(stderr, "Usage: braces filename.txt\n");
	exit(EXIT_FAILURE);
    }

    fin = fopen( argv[1], "rt" );
    if(fin == NULL)
    {
	fprintf(stderr, "Cannot open/find %s\n", argv[1]);
	exit(EXIT_FAILURE);
    }

    stk = CreateStack(40);
    if(stk == NULL)
    {
	fprintf(stderr, "Insufficient Memory\n");
	exit(EXIT_FAILURE);
    }

    stk_el = (struct StkElement *) malloc (sizeof(struct StkElement));
    if(stk_el == NULL)
    {
	fprintf(stderr, "Insufficient Memory\n");
	exit(EXIT_FAILURE);
    }

    line_count = 0;
    while( !feof(fin) )
    {
	if(fgets(buffer, MAX, fin) == NULL)
	    break;
	
	line_count += 1;
	for(i = 0; buffer[i] != '\0'; i++)
	{
	    switch(ch = buffer[i])
	    {
	    case '(':
	    case '[':
	    case '{':
		stk_el->opener = ch;
		stk_el->line_no = line_count;
		if( !PushElement(stk ,stk_el))
		{
		    fprintf(stderr, "Out of stack spaces\n");
		    exit(EXIT_FAILURE);
		}
		break;
	    case '}':
	    case ']':
	    case ')':
		if( !PopElement(stk, stk_el))
		    fprintf(stderr, "Stray %c at line %d\n", ch, line_count);
		else if((ch == ')' && stk_el->opener == '(') ||
			(ch == ']' && stk_el->opener == '[') ||
			(ch == '}' && stk_el->opener == '{'))
			fprintf(stdout, "%c at line %d matched by %c at line %d\n", ch, line_count,
					stk_el->opener, stk_el->line_no);
		else
			fprintf(stderr, "%c at line %d not matched by %c at line %d\n", ch, line_count,
					stk_el->opener, stk_el->line_no);
		break;
	    default:
		continue;
	    }
	}
    }

    if( ViewElement(stk, 0) != NULL)
	while( PopElement(stk, stk_el) != 0)
	    fprintf(stderr, "%c from line %d unmatched\n", stk_el->opener, stk_el->line_no);
    
    fprintf(stderr, "Error checking complete\n");

    fclose(fin);
    return EXIT_SUCCESS;
}

