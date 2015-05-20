
#ifndef LLAPP_H
#define LLAPP_H 

struct NodeData1 {
    char *word;
    unsigned int u;
};

typedef struct NodeData1* pND1;

extern void* CreateData1    ( void* );
extern int   DeleteData1    ( void* );
extern int   DuplicatedNode1 ( Link, Link );
extern int   NodeDataCmp1 ( void*, void* );

struct NodeData2 {
    char* word;
};

typedef struct NodeData2* pND2;

extern void* CreateData2    ( void* );
extern int   DeleteData2    ( void* );
extern int   DuplicatedNode2 ( Link, Link );
extern int   NodeDataCmp2   ( void*, void* );

#endif
