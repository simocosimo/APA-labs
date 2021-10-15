#include "elementi.h"

categoria_t getCategoria(FILE* fi) {
	
	categoria_t c;
	int i;
	fscanf(fi, "%s %d %d %d", c.nome, &c.numes, &c.min, &c.max);
	c.esercizi = malloc(c.numes*sizeof(Elementi));
	for (i = 0; i<c.numes; i++) {
		c.esercizi[i] = getElemento(fi);
	}
	return c;
}

Elementi getElemento(FILE* fi) {
	
	Elementi e;
	fscanf(fi, "%s %f %f", e.nome, &e.punteggio, &e.difficolta);
	e.appetibilita = (e.punteggio) / (e.difficolta);
	return e;
}

void ordinaEs(Elementi* vett, int num) {  
	
	Elementi temp;
	int i, j;

	for (i = 0; i<num; i++) {
		for (j = 0; j<num - i; j++) {
			if (vett[j].appetibilita<vett[j + 1].appetibilita) {
				temp = vett[j];
				vett[j] = vett[j + 1];
				vett[j + 1] = temp;
			}
		}
	}
	return;
}

void print(categoria_t *vettCat, int numCat) {
	
	int i, j;
	for (i = 0; i<numCat; i++) {
		printf("%s %d %d %d", vettCat[i].nome, vettCat[i].numes, vettCat[i].min, vettCat[i].max);
		printf("\n");
		for (j = 0; j<vettCat[i].numes; j++) {
			printf("   %s %f %f", vettCat[i].esercizi[j].nome, vettCat[i].esercizi[j].punteggio, vettCat[i].esercizi[j].difficolta);
			printf("\n");
		}
	}
	return;
}

lista_t* newNode(Elementi* puntatore, lista_t* next) {
	
	lista_t* n;
	n = malloc(sizeof(lista_t));
	n->puntatore = puntatore;
	n->next = next;
	return n;
}

wrapper_t getSol(categoria_t *vettCat, int numCat, float maxDif, float *punteggioTot) {
	
	wrapper_t w;
	int i, j;
	float maxDiff = maxDif;

	w.head = w.tail = NULL;
	for (i = 0; i<numCat; i++) {
		for (j = 0; j<vettCat[i].min; j++) {
			if (vettCat[i].esercizi[j].difficolta<maxDiff) {
				if (w.head == NULL) {
					w.head = (w.tail = newNode(&vettCat[i].esercizi[j], NULL));
				}
				else {
					w.tail->next = newNode(&vettCat[i].esercizi[j], NULL);
					w.tail = w.tail->next;
				}
				maxDiff -= vettCat[i].esercizi[j].difficolta;
				(*punteggioTot) += vettCat[i].esercizi[j].punteggio;
			}
			else return w;
		}
	}

	for (i = 0; i<numCat; i++) {
		for (j = vettCat[i].min; j<vettCat[i].max; j++) {
			if (vettCat[i].esercizi[j].difficolta<maxDiff) {
				w.tail->next = newNode(&vettCat[i].esercizi[j], NULL);
				w.tail = w.tail->next;
				maxDiff -= vettCat[i].esercizi[j].difficolta;
				(*punteggioTot) += vettCat[i].esercizi[j].punteggio;
			}
			else return w;
		}
	}
	return w;
}

void printSol(lista_t* head) {
	
	if (head == NULL)
		return;
	printf("%s %f %f\n", head->puntatore->nome, head->puntatore->punteggio, head->puntatore->difficolta);
	printSol(head->next);
}