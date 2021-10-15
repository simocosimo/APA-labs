#include "ingredienti.h"

ingredienti_w *leggi_ingredienti() {
	
	FILE *fp;
	ingredienti_w *wrapper = malloc(sizeof(*wrapper));
	ingrediente_t *tmp = malloc(sizeof(*tmp));
	int n_ingredienti;

	wrapper->head = NULL; wrapper->tail = NULL;

	if (!(fp = fopen("ingredienti.txt", "r")))
		return NULL;

	fscanf(fp, "%d\n", &n_ingredienti);
	for (int i = 0; i < n_ingredienti; i++) {
		fscanf(fp, "%s%f%f", tmp->nome, &tmp->costo_chilo, &tmp->app_cal);
		if (wrapper->head == NULL) 
			wrapper->head = wrapper->tail = nuovo_ingrediente(tmp);
		else {
			wrapper->tail->next = nuovo_ingrediente(tmp);
			wrapper->tail = wrapper->tail->next;
		}
	}

	fclose(fp);
	return wrapper;
}

ingrediente_t *nuovo_ingrediente(ingrediente_t *tmp) {
	ingrediente_t *r = malloc(sizeof(*r));
	r->app_cal = tmp->app_cal;
	r->costo_chilo = tmp->costo_chilo;
	r->next = NULL;
	strcpy(r->nome, tmp->nome);

	return r;
}

ingrediente_t *cerca_ingrediente(ingredienti_w *wrapper, char nome[MAXC]) {
	
	ingrediente_t *s;
	for (s = wrapper->head; s != NULL; s = s->next) 
		if (strcmp(nome, s->nome) == 0) return s;
	
	return NULL;
}

void libera_ingredienti(ingredienti_w *wrapper) {
	
	ingrediente_t *s, *x;
	for (s = wrapper->head, x = s->next; x != NULL; s = x, x = x->next) {
		wrapper->head = x;
		free(s);
	}
	free(wrapper);
}