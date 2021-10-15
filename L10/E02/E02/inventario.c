#include "inventario.h"

void initInventario(inventario_t ***inv, int dim1, int dim2) {

	(*inv) = malloc((dim1 + 2) * sizeof(int *));
	for (int i = 0; i < dim1 + 2; i++) {
		(*inv)[i] = malloc((dim2 + 2) * sizeof(int));
		if (i == 0 || i == dim1 + 1) {
			for (int j = 0; j < dim2 + 2; j++) (*inv)[i][j] = -1;
		} else {
			for (int j = 0; j < dim2 + 2; j++) (*inv)[i][j] = 0;
			(*inv)[i][0] = -1; (*inv)[i][dim2 + 1] = -1;
		}
	}
}

void liberaInventario(inventario_t **inv, int dim1) {
	for (int i = 0; i < dim1; i++) free(inv[i]);
	free(inv);
}

primo_zero inserisciOggetto(inventario_t **inv, int dim1, int dim2, item_t oggetto) {

	primo_zero primo_z;
	primo_z.i = -1; primo_z.j = -1;
	if (inventarioPieno(inv, dim1, dim2)) return primo_z;
	for (int i = 1; i <= dim1; i++) {
		for (int j = 1; j <= dim2; j++) {
			if (inv[i][j] == 0) {
				primo_z.i = i; primo_z.j = j;
				if (cercaLiberi(inv, oggetto.dim1, oggetto.dim2, primo_z))
					return primo_z;
			}
		}
	}

	primo_z.i = -1; primo_z.j = -1;
	return primo_z;
}

int cercaLiberi(inventario_t **inv, int dim1, int dim2, primo_zero primo_z) {
	
	int ok = 1;
	for (int i = primo_z.i; i < dim1 + primo_z.i; i++) {
		for (int j = primo_z.j; j < dim2 + primo_z.j; j++) {
			if (inv[i][j] != 0) {
				//printf("%d\n", inv[i][j]);
				ok = 0; return ok;
			}
		}
	}

	if (ok) {
		for (int i = primo_z.i; i < dim1 + primo_z.i; i++) {
			for (int j = primo_z.j; j < dim2 + primo_z.j; j++) {
				inv[i][j] = 1;
			}
		}
	}

	return ok;
}

void rimuoviOggetto(inventario_t **inv, item_t oggetto, primo_zero primo_z) {

	for (int i = primo_z.i; i < oggetto.dim1 + primo_z.i; i++) {
		for (int j = primo_z.j; j < oggetto.dim2 + primo_z.j; j++) {
			inv[i][j] = 0;
		}
	}
}

int inventarioPieno(inventario_t **inv, int dim1, int dim2) {
	
	for (int i = 1; i <= dim1; i++) {
		for (int j = 1; j <= dim2; j++) {
			if (inv[i][j] == 0) return 0;
		}
	}
	return 1;
}