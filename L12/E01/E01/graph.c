#include "graph.h"

typedef struct adj Adj;
struct adj { int index; Adj *next; };
struct graph { HT ht; int num_data; Adj **adjList; };

Adj *newAdj(int index, Adj *next) {
	Adj *adj = malloc(sizeof(Adj));
	adj->index = index; adj->next = next;
	return adj;
}

void freeAdjList(Adj *adj) {
	if (adj == NULL) return;
	Adj *t = adj;
	adj = t->next;
	free(t);
	freeAdjList(adj);
	return;
}

GRAPH GRAPHinit(int num_nodes) {
	GRAPH g = malloc(sizeof(*g));
	g->num_data = num_nodes;
	g->ht = HTinit(num_nodes);
	g->adjList = malloc(g->num_data * sizeof(Adj*));
	for (int i = 0; i < g->num_data; i++) g->adjList[i] = NULL;
	return g;
}

GRAPH GRAPHinitFromFile(char *filename) {
	FILE *fp = fopen(filename, "r");
	if (!fp) return NULL;
	GRAPH g;
	int num_nodes, m, v, in_start, in_dest;
	char strNode[MAXC], strStart[MAXC], strDest[MAXC];

	fscanf(fp, "%d\n", &num_nodes);
	g = GRAPHinit(num_nodes);

	// aggiungo i nodi alla hash table
	for (int i = 0; i < g->num_data; i++) {
		fscanf(fp, "%s %d %d\n", strNode, &m, &v);
		HTaddData(g->ht, strNode, m, v);
	}

	// aggiungo le adiacenze
	while (fscanf(fp, "%s %s\n", strStart, strDest) == 2) {
		in_start = HTfindData(g->ht, strStart);
		in_dest = HTfindData(g->ht, strDest);
		g->adjList[in_start] = newAdj(in_dest, g->adjList[in_start]);
		g->adjList[in_dest] = newAdj(in_start, g->adjList[in_dest]);
	}

	return g;
}

void GRAPHfindBestPath(GRAPH g, int pf) {
	int *sol, *bestSol, bestMoney = 0;
	Node *n;
	sol = malloc(g->num_data * sizeof(int));
	bestSol = malloc(g->num_data * sizeof(int));
	for (int i = 0; i < g->num_data; i++) sol[i] = (bestSol[i] = -1);
	GRAPHfindBestPathR(g, 0, 0, 0, pf, &bestMoney, sol, bestSol);

	printf("Il cammino migliore per il personaggio con punti ferita %d e': \n", pf);
	for (int i = 0; i < g->num_data; i++) {
		if (bestSol[i] != -1) {
			n = HTgetData(g->ht, bestSol[i]);
			printf("%s - %d - %d\n", n->strNode, n->m, n->v);
		}
	}
	printf("Monete guadagnate: %d\n", bestMoney);
	return;
}

void GRAPHfindBestPathR(GRAPH g, int pos, int index, int money, int pf, int *bestMoney, int *sol, int *bestSol) {
	// terminazione
	if ((index == g->num_data - 1) || (pos >= g->num_data)) {
		if (money > *bestMoney) {
			*bestMoney = money;
			for (int i = 0; i < g->num_data; i++) bestSol[i] = sol[i];
			bestSol[g->num_data - 1] = g->num_data - 1;
		}
		return;
	}

	// pruning
	Node *n = HTgetData(g->ht, index);
	if ((pf - n->v <= 0) || HTisDataVisited(g->ht, index)) return;

	sol[pos] = index;
	pf -= n->v;
	money += n->m;
	HTchangeVisitedState(g->ht, index, 1);
	for (Adj *a = g->adjList[index]; a != NULL; a = a->next)
		GRAPHfindBestPathR(g, pos + 1, a->index, money, pf, bestMoney, sol, bestSol);

	sol[pos] = -1;
	pf += n->v;
	money -= n->m;
	HTchangeVisitedState(g->ht, index, 0);
	return;
}

void GRAPHfree(GRAPH g) {
	for (int i = 0; i < g->num_data; i++) freeAdjList(g->adjList[i]);
	free(g->adjList); HTfree(g->ht); 
	free(g);
}