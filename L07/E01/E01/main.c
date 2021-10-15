#include "funzioni.h"

int main(int argc, char **argv) {

	int **s, *sol, u[NUMU];
	int x = 0, pos = 0, n, k;

	// costruisco l'insieme U
	for (int i = 0; i < NUMU; i++) u[i] = i + 1;

	if (cover(&s, &n, &k)) {
		// costriusco l'array delle soluzioni
		sol = malloc(n * sizeof(int));
		for (int i = 0; i < n; i++) sol[i] = 0;
		// for (int i = 0; i < k; i++) sol[i] = -1;

		sumset(pos, s, sol, u, x, n, k);
	}

	free(sol); 
	for (int i = 0; i < n; i++) free(s[i]);
	free(s);
	system("PAUSE");
	return 0;
}