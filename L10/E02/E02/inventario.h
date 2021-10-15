#ifndef _INVENTARIO_C_
#define _INVENTARIO_C_

#include "item.h"
typedef struct p_zero primo_zero;
struct p_zero {
	int i, j;
};

typedef int inventario_t;

void initInventario(inventario_t ***inv, int dim1, int dim2);
void liberaInventario(inventario_t **inv, int dim1);
primo_zero inserisciOggetto(inventario_t **inv, int dim1, int dim2, item_t oggetto);
int cercaLiberi(inventario_t **inv, int dim1, int dim2, primo_zero primo_z);
void rimuoviOggetto(inventario_t **inv, item_t oggetto, primo_zero primo_z);
int inventarioPieno(inventario_t **inv, int dim1, int dim2);

#endif
