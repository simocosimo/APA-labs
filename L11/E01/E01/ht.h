#ifndef _HT_H_
#define _HT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo { char *strNode, *strSubNet; } Node;

// ADT prima classe
typedef struct ht *HT;

HT HTInit(int);
int HTaddData(HT, char*, char*);
int HTfindData(HT, char*);
Node *HTgetData(HT, int);
void HTfree(HT);

#endif // !_HT_H_