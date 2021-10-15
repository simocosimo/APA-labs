#include "inventario.h"

#define MAXMARK 3

void powerset(int pos, item_t *oggetti, inventario_t **inv, int *mark, int *sol, int diminv1, int diminv2, int k, int curr_utility, int *best_utility, int *best_sol);
int checkCategorie(int *mark);

int main(int argc, char **argv)
{
	inventario_t **inv;
	item_t *oggetti;
	int n_oggetti = initOggetti(&oggetti, "equip.txt");
	int dim1, dim2;
	int mark[MAXMARK] = { 0 };
	int *sol, *best_sol;
	int best_utility = 0;
	sol = malloc(n_oggetti * sizeof(int));
	for (int i = 0; i < n_oggetti; i++) sol[i] = 0;
	best_sol = malloc(n_oggetti * sizeof(int));

	printf("Inserire le dimensioni dell'inventario: ");
	scanf("%d%d", &dim1, &dim2);

	initInventario(&inv, dim1, dim2);
	
	// cerco soluzioni
	powerset(0, oggetti, inv, mark, sol, dim1, dim2, n_oggetti, 0, &best_utility, best_sol);
	if (best_utility != 0) {
		printf("Migliore utilita': %d\n", best_utility);
		for (int i = 0; i < n_oggetti; i++) {
			if (best_sol[i]) {
				printf("- %s %s %d %d %d\n", oggetti[i].nome, oggetti[i].cat, oggetti[i].dim1, oggetti[i].dim2, oggetti[i].utility);
			}
		}
	} else {
		printf("Nessuna soluzione disponibile.\n");
	}

	liberaInventario(inv, dim1);
	liberaOggetti(oggetti);
	system("PAUSE");
	return 0;
}

void powerset(int pos, item_t *oggetti, inventario_t **inv, int *mark, int *sol, int diminv1, int diminv2, int k, int curr_utility, int *best_utility, int *best_sol) {

	primo_zero primo_z;
	if (pos >= k || inventarioPieno(inv, diminv1, diminv2)) {
		if (checkCategorie(mark)) {
			if (curr_utility > *best_utility) {
				*best_utility = curr_utility;
				for (int i = 0; i < k; i++) best_sol[i] = sol[i];
			}
		}
		return;
	}

	primo_z = inserisciOggetto(inv, diminv1, diminv2, oggetti[pos]);
	if (primo_z.i == -1 && primo_z.j == -1) {
		sol[pos] = 0;
		powerset(pos + 1, oggetti, inv, mark, sol, diminv1, diminv2, k, curr_utility, best_utility, best_sol);
		return;
	}

	sol[pos] = 1;
	curr_utility += oggetti[pos].utility;
	if (strcmp(oggetti[pos].cat, "arma") == 0) mark[0]++; 
	else if (strcmp(oggetti[pos].cat, "armatura") == 0) mark[1]++; 
	else if (strcmp(oggetti[pos].cat, "pozione") == 0) mark[2]++;
	powerset(pos + 1, oggetti, inv, mark, sol, diminv1, diminv2, k, curr_utility, best_utility, best_sol);

	sol[pos] = 0;
	rimuoviOggetto(inv, oggetti[pos], primo_z);
	curr_utility -= oggetti[pos].utility;
	if (strcmp(oggetti[pos].cat, "arma") == 0) mark[0]++;
	else if (strcmp(oggetti[pos].cat, "armatura") == 0) mark[1]++;
	else if (strcmp(oggetti[pos].cat, "pozione") == 0) mark[2]++;
	powerset(pos + 1, oggetti, inv, mark, sol, diminv1, diminv2, k, curr_utility, best_utility, best_sol);
	
}

int checkCategorie(int *mark) {

	int ok = 1;
	for (int i = 0; i < MAXMARK; i++) {
		if (mark[i] < 1) ok = 0;
	}

	return ok;
}