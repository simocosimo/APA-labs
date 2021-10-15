#include "ricette.h"

ricette_w *leggi_ricette() {

	FILE *fp;
	ricette_w *wrapper = malloc(sizeof(*wrapper));
	ricetta_t *tmp = malloc(sizeof(*tmp));
	int n_ricette, n_ingredienti;

	wrapper->head = NULL; wrapper->tail = NULL;

	if (!(fp = fopen("ricette.txt", "r")))
		return NULL;

	fscanf(fp, "%d\n", &n_ricette);
	for (int i = 0; i < n_ricette; i++) {
		fscanf(fp, "%s%d%d\n", tmp->titolo, &tmp->tempo_min, &n_ingredienti);
		if (wrapper->head == NULL)
			wrapper->head = wrapper->tail = nuova_ricetta(fp, tmp, n_ingredienti);
		else {
			wrapper->tail->next = nuova_ricetta(fp, tmp, n_ingredienti);
			wrapper->tail = wrapper->tail->next;
		}
	}

	fclose(fp);
	return wrapper;
}

ricetta_t *nuova_ricetta(FILE *fp, ricetta_t *tmp, int n_ingredienti) {
	
	ricetta_t *r = malloc(sizeof(*r));
	ingrediente_t *tmpI = malloc(sizeof(*tmp));

	strcpy(r->titolo, tmp->titolo);
	r->tempo_min = tmp->tempo_min;
	r->ingredienti = nuovo_wrapper_ingredienti();
	r->ingredienti = leggi_ingredienti_ricetta(fp, r->ingredienti, n_ingredienti);
	r->next = NULL;

	return r;
}

void stampa_ricetta_nome(ricette_w *wrapper) {

	ricetta_t *s;
	ingrediente_t *x;
	char titolo[MAXC];
	
	printf("\nInserisci il titolo della ricetta: ");
	scanf("%s", titolo);

	for (s = wrapper->head; s != NULL; s = s->next) {
		if (strcmp(s->titolo, titolo) == 0) {
			printf("%s - %d minuti\n", s->titolo, s->tempo_min);
			for (x = s->ingredienti->head; x != NULL; x = x->next)
				printf("\t%s - %.2fg\n", x->nome, x->qta);
		}
	}
}

void stampa_ricetta_ingr(ricette_w *wrapper) {

	ricetta_t *s;
	ingrediente_t *x;
	char ingr[MAXC];
	int trovato = 0;

	printf("\nInserisci l'ingrediente: ");
	scanf("%s", ingr);

	for (s = wrapper->head; s != NULL; s = s->next) {
		x = cerca_ingrediente_lista(s->ingredienti, ingr);
		if (x != NULL) printf("- %s\n", s->titolo);
	}

}

void costo_ricetta(ricette_w *wrapper, ingrediente_t *array, int n) {

	ricetta_t *s;
	ingrediente_t *x, tmp;
	char titolo[MAXC];
	float costo = 0;

	printf("\nInserisci il titolo della ricetta: ");
	scanf("%s", titolo);

	for (s = wrapper->head; s != NULL; s = s->next) {
		if (strcmp(s->titolo, titolo) == 0) {
			for (x = s->ingredienti->head; x != NULL; x = x->next) {
				tmp = cerca_ingrediente_array(array, n, x->nome);
				costo += ((tmp.costo_chilo / (float)1000) * x->qta);
			}
		}
	}
	printf("Il costo della ricetta %s è %.2f.\n", titolo, costo);
}

void app_cal_ricetta(ricette_w *wrapper, ingrediente_t *array, int n) {

	ricetta_t *s;
	ingrediente_t *x, tmp;
	char titolo[MAXC];
	float cal = 0;

	printf("\nInserisci il titolo della ricetta: ");
	scanf("%s", titolo);

	for (s = wrapper->head; s != NULL; s = s->next) {
		if (strcmp(s->titolo, titolo) == 0) {
			for (x = s->ingredienti->head; x != NULL; x = x->next) {
				tmp = cerca_ingrediente_array(array, n, x->nome);
				cal += (tmp.costo_chilo * x->qta);
			}
		}
	}
	printf("L'apporto calorico della ricetta %s è %.2f.\n", titolo, cal);
}

void nuova_ricetta_input(ricette_w *wrapper, ingrediente_t *ingredienti, int n) {
	
	ricetta_t *tmp = malloc(sizeof(*tmp));
	ingrediente_t *ingr = malloc(sizeof(*ingr));
	ingrediente_t check;
	int n_ingr;

	printf("Inserisci il nome e la durata di preparazione in minuti: ");
	scanf("%s%d", tmp->titolo, &tmp->tempo_min);
	printf("Quanti ingredienti ci sono? ");
	scanf("%d", &n_ingr);
	tmp->ingredienti = nuovo_wrapper_ingredienti();
	for (int i = 0; i < n_ingr; i++) {
		printf("Inserisci il nome e la q.ta: ");
		scanf("%s%f", ingr->nome, &ingr->qta);
		check = cerca_ingrediente_array(ingredienti, n, ingr->nome);
		if (strcmp(check.nome, "void") == 0) {
			printf("Ingrediente inesistente.\n");
			i--;
		} else {
			if (tmp->ingredienti->head == NULL) {
				tmp->ingredienti->head = tmp->ingredienti->tail = nuovo_ingrediente(ingr);
			} else {
				tmp->ingredienti->tail->next = nuovo_ingrediente(ingr);
				tmp->ingredienti->tail = tmp->ingredienti->tail->next;
			}
		}
	}

	wrapper->tail->next = tmp;
	wrapper->tail = wrapper->tail->next;
	wrapper->tail->next = NULL;
	free(ingr); 
}

void stampa_ricette(ricette_w *wrapper) {

	ricetta_t *s;
	ingrediente_t *ingr;

	if (wrapper->head == NULL) return;
	else {
		for (s = wrapper->head; s != NULL; s = s->next) {
			printf("Titolo: %s\nTempo di preparazione: %d min.\n", s->titolo, s->tempo_min);
			printf("Lista di ingredienti:\n");
			for (ingr = s->ingredienti->head; ingr != NULL; ingr = ingr->next) {
				printf("\t-%s %.2f g\n", ingr->nome, ingr->qta);
			}
			printf("\n");
		}
	}
}

void libera_ricette(ricette_w *wrapper) {
	ricetta_t *s, *x;
	for (s = wrapper->head, x = s->next; x != NULL; s = x, x = x->next) {
		wrapper->head = x;
		libera_ingredienti(s->ingredienti);
		free(s);
	}
	free(wrapper);
}