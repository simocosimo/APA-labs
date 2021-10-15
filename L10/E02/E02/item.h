#ifndef _ITEM_H
#define _ITEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 255

typedef struct item item_t;

struct item {
	char nome[MAXC];
	char cat[MAXC];
	int dim1, dim2, utility, primo_zero;
};

int initOggetti(item_t **oggetti, char *file);
void liberaOggetti(item_t *oggetti);

#endif