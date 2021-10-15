#include "graph.h"

int main(int argc, char **argv) {
	GRAPH g;
	int pf;

	if (argc != 2) return 1;
	g = GRAPHinitFromFile(argv[1]);

	printf("Inserire i punti ferita del giocatore: ");
	scanf("%d", &pf);

	GRAPHfindBestPath(g, pf);
	system("PAUSE");
	return 0;
}