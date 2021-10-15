#ifndef elementi_h
#define elementi_h

#include <stdio.h>
#include <stdlib.h>

typedef struct el {
	char nome[256];
	float punteggio;
	float difficolta;
	float appetibilita;
}Elementi;

typedef struct cate {
	char nome[256];
	int numes;
	int min;
	int max;
	Elementi *esercizi;
}categoria_t;

typedef struct lista_t {
	Elementi *puntatore;
	struct lista_t *next;
}lista_t;

typedef struct {
	lista_t* head;
	lista_t* tail;
}wrapper_t;

categoria_t getCategoria(FILE* fi);
Elementi getElemento(FILE* fi);
void ordinaEs(Elementi* vett, int num);
void print(categoria_t *vettCat, int numCat);
wrapper_t getSol(categoria_t *vettCat, int numCat, float maxDif, float *punteggioTot);
lista_t* newNode(Elementi* puntatore, lista_t* next);
void printSol(lista_t* head);

#endif