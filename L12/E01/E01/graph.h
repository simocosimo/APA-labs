#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "ht.h"

#define MAXC 30

typedef struct graph *GRAPH;

GRAPH GRAPHinit(int);
GRAPH GRAPHinitFromFile(char*);
void GRAPHfindBestPath(GRAPH, int);
void GRAPHfindBestPathR(GRAPH, int, int, int, int, int*, int*, int*);
void GRAPHfree(GRAPH);

#endif