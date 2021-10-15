#include "item.h"

int initOggetti(item_t **oggetti, char *file) {
	
	FILE *fp = fopen(file, "r");
	int n;
	item_t tmp;

	fscanf(fp, "%d\n", &n);
	(*oggetti) = malloc(n * sizeof(item_t));

	for (int i = 0; i < n; i++) {
		fscanf(fp, "\t%s %s %d %d %d\n", tmp.nome, tmp.cat, &tmp.dim1, &tmp.dim2, &tmp.utility);
		tmp.primo_zero = -1;
		(*oggetti)[i] = tmp;
	}

	fclose(fp);
	return n;
}

void liberaOggetti(item_t *oggetti) {
	free(oggetti);
}

