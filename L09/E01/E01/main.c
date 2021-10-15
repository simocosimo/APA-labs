#include "elementi.h"

int main() 
{
	FILE* fi;
	categoria_t *vettCat;
	wrapper_t soluzione;
	int numCat, i;
	float maxDiff, punteggio = 0;
	
	fi = fopen("elementi.txt", "r");
	fscanf(fi, "%d", &numCat);

	vettCat = malloc(numCat*sizeof(categoria_t));
	for (i = 0; i<numCat; i++) {
		vettCat[i] = getCategoria(fi);
	}
	
	fclose(fi);

	for (i = 0; i<numCat; i++)
		ordinaEs(vettCat[i].esercizi, vettCat[i].numes);

	printf("Inserire il valore massimo di difficoltà:");
	scanf("%f", &maxDiff);

	soluzione = getSol(vettCat, numCat, maxDiff, &punteggio);
	printSol(soluzione.head);

	system("PAUSE");
	return 0;
}