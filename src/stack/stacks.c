
#define IN_STACK_LIB 1

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "src/stacks.h"

void ClearStack( Stack *stack)
{
    stack->top = -1;
}

Stack* CreateStack( int how_many )
{
    Stack *pstk;

    assert( how_many > 0);
    pstk = (Stack*) malloc (sizeof(Stack) );
    if(pstk == NULL)
	return NULL;

    pstk->stack_size = how_many;
    pstk->base = (struct StkElement*) malloc ( how_many*sizeof(struct StkElement) );
    if(pstk->base == NULL)
	return NULL;

    pstk->min_stack = 0;
    pstk->max_stack = how_many - 1;

    ClearStack(pstk);
    return pstk;
}

int PopElement ( Stack *this_stack, struct StkElement *destination )
{
    if( this_stack->top == -1)
	return 0;

    memmove( destination, &((this_stack->base)[this_stack->top]),
			  sizeof(struct StkElement));
    this_stack->top -= 1;
}

int PushElement ( Stack *this_stack, struct StkElement *to_push )
{
    if(this_stack->top == this_stack->max_stack)
	return 0;
    this_stack->top += 1;

    memmove(&((this_stack->base)[this_stack->top]), to_push, sizeof(struct StkElement));
    return 1;
}

struct StkElement* ViewElement( Stack *this_stack, int which_element )
{
    if(this_stack->top == -1)
	return NULL;

    if(this_stack->top - which_element < 0)
	return NULL;

    return (&((this_stack)->base[this_stack->top - which_element]));
}
