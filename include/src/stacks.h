
#ifndef STACKS_H
#define STACKS_H

#ifdef IN_STACK_LIB
#define StkExtern
#else
#define StkExtern extern
#endif

struct stack_struct {
    struct StkElement *base;
    int                stack_size;
    int                min_stack;
    int                max_stack;
    int		       top;
};

typedef struct stack_struct Stack;

StkExtern void   ClearStack  ( Stack* );
StkExtern Stack* CreateStack ( int ); 
StkExtern int    PopElement  ( Stack*, struct StkElement* );
StkExtern int    PushElement ( Stack*, struct StkElement* ); 
StkExtern struct StkElement* ViewElement ( Stack*, int );

struct StkElement{
    int  line_no;
    char opener;
};

#endif
