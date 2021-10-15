#ifndef PQ_H_DEF
#define PQ_H_DEF

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "item.h"

typedef struct pqueue *PQ;

PQ PQinit(int);
int PQempty(PQ);
Item PQget(PQ);
void PQinsert(PQ, Item);
void HEAPify(PQ, int);
void PQfree(PQ);

#endif
