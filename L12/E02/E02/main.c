#include "graph.h"

#define MAXF 20

int main(int argc, char **argv) {
	GRAPH g;
	char filename[MAXF];

	printf("Inserisci il nome del file: ");
	scanf("%s", filename);

	g = GRAPHinitFromFile(filename);
	if (g != NULL)
		er_wrapper(g);

	system("PAUSE");
	return 0;
}