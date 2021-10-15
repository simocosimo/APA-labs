#ifndef _ITEM_H_
#define _ITEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node Node;
struct node { char *strNode; int m; int v; int visited; };

Node *newNode(char*, int, int);
void freeNode(Node*);

#endif