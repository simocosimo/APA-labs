#ifndef _HT_H_
#define _HT_H_

#include "item.h"

typedef struct ht *HT;

HT HTinit(int);
int HTaddData(HT, char*, int, int);
int HTfindData(HT, char*);
int HTisDataVisited(HT, int);
void HTchangeVisitedState(HT, int, int);
Node *HTgetData(HT, int);
void HTfree(HT);

#endif