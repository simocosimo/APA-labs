#ifndef	_GRAPH_H_
#define _GRAPH_H_

#include "ht.h"

#define MAXC 30

typedef struct graph *GRAPH;

GRAPH GRAPHinitFromFile(char*);
void GRAPHprintNodes(GRAPH);
void GRAPHprintAdjacency(GRAPH, char*);
void GRAPHwriteAdjMatrix(GRAPH);
void GRAPHfree(GRAPH);

#endif // !_GRAPH_H_