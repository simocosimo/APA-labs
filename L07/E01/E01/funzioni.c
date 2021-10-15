#include "funzioni.h"

int cover(int ***s, int *n, int *k) {

	FILE *fp;
	int stop = 0;

	if (!(fp = fopen("matrice.txt", "r")))
		return -1;

	fscanf(fp, "%d\n", n);

	// alloco dinamicamente la matrice
	(*s) = malloc((*n) * sizeof(int *));
	for (int i = 0; i < (*n); i++) (*s)[i] = malloc(MAXC * sizeof(int));

	// leggo la matrice e la memorizzo
	for (int i = 0; i < (*n); i++) {
		stop = 0;
		for (int j = 0; j < MAXC && !stop; j++) {
			fscanf(fp, "%d", &((*s)[i][j]));
			if ((*s)[i][j] == 0) stop = 1;
		}
	}

	// acquisisco il valore di k, se non è intero esco
	printf("Inserire il valore di k: ");
	if (!scanf("%d", k)) return -1;

	return 1;
}

void sumset(int pos, int **s, int *sol, int *u, int x, int n, int k) {
	
	// terminazione
	if (pos >= n) {
		if (x == k) {
			// controllo se la soluzione è valida visto che sol è pieno
			if (check(u, s, sol, n)) {
				printf("{ ");
				for (int i = 0; i < n; i++) {
					if(sol[i] == 1) printf("S%d ", i);
				}
				printf("}\n");
				return;
			}
		}
		return;
	}
	// prendo l'oggetto considerato
	sol[pos] = 1;
	sumset(pos + 1, s, sol, u, x + 1, n, k);

	// backtrack
	sol[pos] = 0;
	sumset(pos + 1, s, sol, u, x, n, k);
	
}

int check(int *u, int **s, int *sol, int n) {

	int *test_sol = malloc(n * MAXC * sizeof(int));
	int cnt = 0, trovato = 0;
	int corr[NUMU] = { 0 };

	for (int i = 0; i < n; i++) {
		if (sol[i] == 1) {
			for (int j = 0; j < MAXC && s[i][j] != 0; j++) {
				test_sol[cnt] = s[i][j];
				cnt++;
			}
		}
	}

	// controllo se il vettore appena creato corrisponde a u
	for (int i = 0; i < n * NUMU; i++) {
		trovato = 0;
		for (int j = 0; j < NUMU && !trovato; j++) {
			if (test_sol[i] == u[j]) {
				corr[j]++;
				trovato = 1;
			}
		}
	}

	free(test_sol);
	for (int i = 0; i < NUMU; i++) {
		if (corr[i] != 1) return 0;
	}
	return 1;
}