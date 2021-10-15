#ifndef _RICETTE_H_
#define _RICETTE_H_

#include "ingredienti.h"

typedef struct ricetta ricetta_t;
typedef struct ricette ricette_w;

struct ricetta {
	char titolo[MAXC];
	int tempo_min;
	ingredienti_w *ingredienti;
	ricetta_t *next;
};

struct ricette {
	ricetta_t *head;
	ricetta_t *tail;
};

ricette_w *leggi_ricette();
ricetta_t *nuova_ricetta(FILE *fp, ricetta_t *tmp, int n_ingredienti);
void stampa_ricetta_nome(ricette_w *wrapper);
void stampa_ricetta_ingr(ricette_w *wrapper);
void costo_ricetta(ricette_w *wrapper, ingrediente_t *array, int n);
void app_cal_ricetta(ricette_w *wrapper, ingrediente_t *array, int n);
void nuova_ricetta_input(ricette_w *wrapper, ingrediente_t *ingredienti, int n);
void stampa_ricette(ricette_w *wrapper);
void libera_ricette(ricette_w *wrapper);

#endif