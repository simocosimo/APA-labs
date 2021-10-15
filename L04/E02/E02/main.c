#include <stdio.h>
#include <stdlib.h>

void malloc2dP(int ***P, int *nr, int *nc);
void arrayD(int **P, int nr, int nc, int ***d, int ***ad);
int misuraD(int nr, int nc, int i, int j);
void assegnaAD(int **P, int ***d, int nr, int nc);
void assegnaD(int **P, int ***d, int nr, int nc);
void freeMemory(int **P, int **d, int **ad, int nr, int nc);

int main(int argc, char **argv)
{
	int **mat, nr, nc;
	int **d, **ad;

	malloc2dP(&mat, &nr, &nc);
	arrayD(mat, nr, nc, &d, &ad);

	freeMemory(mat, d, ad, nr, nc);
	return 0;
}

void malloc2dP(int ***P, int *nr, int *nc)
{
	FILE *fp;

	fp = fopen("matrice.txt", "r");
	fscanf(fp, "%d %d\n", nr, nc);

	// ALLOCO LA MATRICE IN MODO STANDARD
	*P = malloc((*nr) * sizeof(int*));
	for (int i = 0; i < *nr; i++) {
		(*P)[i] = malloc((*nc) * sizeof(int));

		for (int j = 0; j < *nc; j++) {
			fscanf(fp, "%d", &((*P)[i][j]));
		}
	} 

	// chiudo il file
	fclose(fp);
}

void arrayD(int **P, int nr, int nc, int ***d, int ***ad)
{
	int n = nr + nc - 1;
	int num, cnt = 0;
	*d = malloc(n * sizeof(int *));
	*ad = malloc(n * sizeof(int *));

	// conto quanti elementi allocare
	for (int i = 0; i < nr; i++) {
		if (i == 0) {
			for (int j = nc - 1; j >= 0; j--) {
				num = misuraD(nr, nc, i, j);
				(*d)[cnt] = malloc(num * sizeof(int));
				(*ad)[cnt] = malloc(num * sizeof(int));
				cnt++;
			}
		} else {
			num = misuraD(nr, nc, i, i);
			(*d)[cnt] = malloc(num * sizeof(int));
			(*ad)[cnt] = malloc(num * sizeof(int));
			cnt++;
		}
	}

	// assegno e stampo i valori 
	assegnaAD(P, ad, nr, nc);
	printf("\n");
	assegnaD(P, d, nr, nc);

}

int misuraD(int nr, int nc, int i, int j)
{
	int num = 0;
	while (i < nr && j < nc) {
		num++;
		i++;
		j++;
	}

	return num;
}

void assegnaD(int **P, int ***d, int nr, int nc)
{
	int n = nr + nc - 1;
	int *occ = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) occ[i] = 0;

	// aggiungo i valori diagonali
	for (int i = 0; i < nr; i++) {
		for (int j = nc - 1; j >= 0; j--) {
			(*d)[nc - (j + 1) + i][occ[nc - (j + 1) + i]] = P[i][j];
			occ[nc - (j + 1) + i]++;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < occ[i]; j++) {
			printf("%d ", (*d)[i][j]);
		}
		printf("\n");
	}

	// libero il vettore delle occorrenze
	free(occ);
}

void assegnaAD(int **P, int ***d, int nr, int nc)
{
	int n = nr + nc - 1;
	int *occ = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) occ[i] = 0;

	// aggiungo i valori antidiagonali
	for (int j = 0; j < nc; j++) {
		for (int i = 0; i < nr; i++) {
			(*d)[i + j][occ[i + j]] = P[i][j];
			occ[i + j]++;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < occ[i]; j++) {
			printf("%d ", (*d)[i][j]);
		}
		printf("\n");
	}

	// libero il vettore delle occorrenze
	free(occ);
}

void freeMemory(int **P, int **d, int **ad, int nr, int nc)
{
	int n = nr + nc - 1;
	for (int i = 0; i < nr; i++) { free(P[i]); }
	for (int i = 0; i < n; i++) {
		free(d[i]); free(ad[i]);
	}
	free(P); free(d); free(ad);
}