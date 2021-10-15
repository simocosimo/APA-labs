#include "ingredienti.h"

int leggi_ingredienti_file(ingrediente_t **array) {
	
	FILE *fp;
	ingrediente_t tmp;
	int n_ingredienti;

	if (!(fp = fopen("ingredienti.txt", "r")))
		return NULL;

	fscanf(fp, "%d\n", &n_ingredienti);
	(*array) = malloc(n_ingredienti * sizeof(ingrediente_t));
	for (int i = 0; i < n_ingredienti; i++) {
		fscanf(fp, "%s%f%f", tmp.nome, &tmp.costo_chilo, &tmp.app_cal);
		tmp.next = NULL;
		(*array)[i] = tmp;
	}

	return n_ingredienti;
}

ingredienti_w *leggi_ingredienti_ricetta(FILE *fp, ingredienti_w *wRicetta, int n_ingredienti) {

	ingrediente_t *tmp = malloc(sizeof(*tmp));
	tmp->app_cal = 0; tmp->costo_chilo = 0;

	for (int i = 0; i < n_ingredienti; i++) {
		fscanf(fp, "\t%s%f\n", tmp->nome, &tmp->qta);
		if (wRicetta->head == NULL)
			wRicetta->head = wRicetta->tail = nuovo_ingrediente(tmp);
		else {
			wRicetta->tail->next = nuovo_ingrediente(tmp);
			wRicetta->tail = wRicetta->tail->next;
		}
	}
	free(tmp);
	return wRicetta;
}

ingredienti_w *nuovo_wrapper_ingredienti() {
	ingredienti_w *n = malloc(sizeof(*n));
	n->head = n->tail = NULL;
	return n;
}

ingrediente_t *nuovo_ingrediente(ingrediente_t *tmp) {
	ingrediente_t *r = malloc(sizeof(*r));
	r->app_cal = tmp->app_cal;
	r->costo_chilo = tmp->costo_chilo;
	r->qta = tmp->qta;
	r->next = NULL;
	strcpy(r->nome, tmp->nome);

	return r;
}

ingrediente_t *cerca_ingrediente_lista(ingredienti_w *wrapper, char nome[MAXC]) {

	ingrediente_t *s;
	for (s = wrapper->head; s != NULL; s = s->next)
		if (strcmp(nome, s->nome) == 0) return s;

	return NULL;
}

ingrediente_t cerca_ingrediente_array(ingrediente_t *array, int n,  char nome[MAXC]) {

	ingrediente_t tmp;
	strcpy(tmp.nome, "void"); 
	for (int i = 0; i < n; i++) {
		if (strcmp(nome, array[i].nome) == 0) {
			tmp = array[i];
		}
	}
	return tmp;
}

void stampa_ingrediente(ingrediente_t *wrapper, int n) {

	char ingr[MAXC];
	ingrediente_t tmp;

	printf("Inserisci l'ingrediente: ");
	scanf("%s", ingr);
	tmp = cerca_ingrediente_array(wrapper, n, ingr);
	printf("Nome: %s\n", tmp.nome);
	printf("Costo al chilo: %.2f\n", tmp.costo_chilo);
	printf("Apporto calorico al grammo: %.2f\n\n", tmp.app_cal);

}

void stampa_ingredienti(ingrediente_t *wrapper, int n) {

	printf("Elenco ingredienti:\n");
	for (int i = 0; i < n; i++) {
		printf("%d)", i + 1);
		printf("Nome: %s\n", wrapper[i].nome);
		printf("Costo al chilo: %.2f\n", wrapper[i].costo_chilo);
		printf("Apporto calorico al grammo: %.2f\n\n", wrapper[i].app_cal);
	}
}

void libera_ingredienti(ingredienti_w *wrapper) {

	ingrediente_t *s, *x;
	for (s = wrapper->head, x = s->next; x != NULL; s = x, x = x->next) {
		wrapper->head = x;
		free(s);
	}
	free(wrapper);
}