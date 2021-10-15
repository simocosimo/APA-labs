#include "graph.h"

int main(int argc, char **argv) {
	GRAPH g;
	char strNode[MAXC];

	if (argc != 2) return 1;
	g = GRAPHinitFromFile(argv[1]);

	printf("1) Stampa di tutti i vertici del grafo...\n");
	GRAPHprintNodes(g);
	printf("2) Inserire il nome di un vertice: ");
	scanf("%s", strNode);
	GRAPHprintAdjacency(g, strNode);
	printf("\n3) Creazione della matrice delle adiacenze a partire dalla lista delle adiacenze...\n");
	GRAPHwriteAdjMatrix(g);

	GRAPHfree(g);
	system("PAUSE");
	return 0;
}