#include "graph.h"

typedef struct adjacency Adj;

struct adjacency { int index; int weight; Adj *next; };
struct graph { HT ht; int num_nodes; int **adjMatrix; Adj **adjList; };

Adj *newAdj(int index, int weight, Adj *next) {
	Adj *a = malloc(sizeof(Adj));
	a->index = index; a->weight = weight; a->next = next;
	return a;
}

GRAPH GRAPHcreate(int num_nodes) {
	GRAPH g = malloc(sizeof(*g));
	g->ht = HTInit(num_nodes);
	g->num_nodes = num_nodes;
	g->adjMatrix = malloc(num_nodes * sizeof(int));
	g->adjList = malloc(num_nodes * sizeof(Adj*));
	for (int i = 0; i < num_nodes; i++) {
		g->adjMatrix[i] = malloc(num_nodes * sizeof(int));
		g->adjList[i] = NULL;
		for (int j = 0; j < num_nodes; j++) 
			g->adjMatrix[i][j] = 0;
	}
	return g;
}

GRAPH GRAPHinitFromFile(char *filename) {
	FILE *fp = fopen(filename, "r");
	if (!fp) return NULL;
	GRAPH g;
	int num_nodes, weight, in_s, in_d;
	char strNode[MAXC], strSubNet[MAXC];
	char strStart[MAXC], strDest[MAXC];

	// leggo la prima linea, numero di vertici
	fscanf(fp, "%d\n", &num_nodes);
	g = GRAPHcreate(num_nodes);

	// leggo le righe con i vertici e le sottoreti
	for (int i = 0; i < num_nodes; i++) {
		fscanf(fp, "%s %s\n", strNode, strSubNet);
		// Aggiungo il nodo alla tabella di hash 
		if (HTaddData(g->ht, strNode, strSubNet) < 0) return NULL;
	}

	// inizio a leggere gli archi e a riempire la lista delle adiacenze
	while (fscanf(fp, "%s %s %d\n", strStart, strDest, &weight) == 3) {
		in_s = HTfindData(g->ht, strStart);
		in_d = HTfindData(g->ht, strDest);
		if (in_s >= 0 && in_d >= 0) {
			g->adjList[in_s] = newAdj(in_d, weight, g->adjList[in_s]);
			g->adjList[in_d] = newAdj(in_s, weight, g->adjList[in_d]);
		} else return NULL;
	}

	fclose(fp);
	return g;
}

void GRAPHprintNodes(GRAPH g) {
	Node *n;
	for (int i = 0; i < g->num_nodes; i++) {
		n = HTgetData(g->ht, i);
		printf("Nodo numero %d: %s --> %s\n", i, n->strNode, n->strSubNet);
	}
}

void GRAPHprintAdjacency(GRAPH g, char *strNode) {
	int in = HTfindData(g->ht, strNode);
	printf("Archi del nodo %s:\n", strNode);
	for (Adj *x = g->adjList[in]; x != NULL; x = x->next) 
		printf("\t%s -- %d -- %s\n", strNode, x->weight, HTgetData(g->ht, x->index)->strNode);
	
	printf("\tNodi adiacenti: ");
	for (Adj *x = g->adjList[in]; x != NULL; x = x->next)
		printf("%s ", HTgetData(g->ht, x->index)->strNode);
}

void GRAPHwriteAdjMatrix(GRAPH g) {
	for (int i = 0; i < g->num_nodes; i++) {
		for (Adj *x = g->adjList[i]; x != NULL; x = x->next) {
			g->adjMatrix[i][x->index] = x->weight;
			g->adjMatrix[x->index][i] = x->weight;
		}
	}

	// stampo la matrice per provare la creazione
	for (int i = 0; i < g->num_nodes; i++) {
		for (int j = 0; j < g->num_nodes; j++)
			printf("%d ", g->adjMatrix[i][j]);
		printf("\n");
	}
}

void Adjfree(Adj *a) {
	if (a == NULL) return;
	Adj *t = a;
	a = t->next;
	free(t);
	Adjfree(a);
	return;
}

void GRAPHfree(GRAPH g) {
	for (int i = 0; i < g->num_nodes; i++) {
		free(g->adjMatrix[i]); Adjfree(g->adjList[i]);
	}
	free(g->adjList); free(g->adjMatrix);
	HTfree(g->ht);
	free(g);
}