#ifndef _INGREDIENTI_H_
#define _INGREDIENTI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 255

typedef struct ingrediente ingrediente_t;
typedef struct ingredienti ingredienti_w;

struct ingrediente {
	char nome[MAXC];
	float costo_chilo;
	float app_cal;
	float qta;
	ingrediente_t *next;
};

struct ingredienti {
	ingrediente_t *head;
	ingrediente_t *tail;
};

int leggi_ingredienti_file(ingrediente_t **array);
ingredienti_w *leggi_ingredienti_ricetta(FILE *fp, ingredienti_w *wRicetta, int n_ingredienti);
ingredienti_w *nuovo_wrapper_ingredienti();
ingrediente_t *nuovo_ingrediente(ingrediente_t *tmp);
ingrediente_t *cerca_ingrediente_lista(ingredienti_w *wrapper, char nome[MAXC]);
ingrediente_t cerca_ingrediente_array(ingrediente_t *array, int n, char nome[MAXC]);
void stampa_ingrediente(ingrediente_t *wrapper, int n);
void stampa_ingredienti(ingrediente_t *wrapper, int n);
void libera_ingredienti(ingredienti_w *wrapper);


#endif