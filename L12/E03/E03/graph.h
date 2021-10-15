#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct graph *GRAPH;

GRAPH GRAPHinit(int);
GRAPH GRAPHinitFromFile(char*);
void er_wrapper(GRAPH);
void GRAPHfree(GRAPH);

#endif