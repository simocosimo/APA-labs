#include "ingredienti.h"

typedef struct ricetta {
	char titolo[MAXC];
	int tempo_min;
	char **ingredienti;
	float *grammi;
}ricetta_t;

void menu(int *stop, ricetta_t *ricetta, ingredienti_w *wrapper);
void nuova_ricetta(ricetta_t *ricetta, ingredienti_w *wrapper);

int main(int argc, char **argv)
{
	ingredienti_w *w_ingredienti;
	ricetta_t ricetta;
	int stop = 0;

	w_ingredienti = leggi_ingredienti();
	while (!stop)
		menu(&stop, &ricetta, w_ingredienti);

	libera_ingredienti(w_ingredienti);
	system("PAUSE");
	return 0;
}

void menu(int *stop, ricetta_t *ricetta, ingredienti_w *wrapper) {
	
	int scelta;

	printf("Menu:\n");
	printf("1) Inserisci una nuova ricetta.\n");
	printf("2) Fine.\n");
	scanf("%d", &scelta);

	if (scelta == 2) *stop = 1;
	else if (scelta == 1) nuova_ricetta(ricetta, wrapper);
}

void nuova_ricetta(ricetta_t *ricetta, ingredienti_w *wrapper) {

	float costo = 0, apporto_cal = 0;
	int fine = 0, j = 1, i;
	char nome_l[MAXC];
	ingrediente_t *ingrediente_l = NULL;

	printf("Inserisci un titolo per la ricetta: ");
	scanf("%s", ricetta->titolo);
	printf("Inserisci il tempo di preparazione in minuti: ");
	scanf("%d", &ricetta->tempo_min);

	ricetta->ingredienti = malloc(j * sizeof(char *));
	for (int i = 0; i < j; i++) ricetta->ingredienti[i] = NULL;

	ricetta->grammi = malloc(j * sizeof(int));
	for (int i = 0; i < j; i++) ricetta->grammi[i] = 0;

	for (i = 0; !fine; i++) {
		printf("\nInserisci il nome del %d ingrediente: ", i + 1);
		scanf("%s", nome_l);
		if (strcmp(nome_l, "fine") == 0) { 
			fine = 1; i--;
		} else if ((ingrediente_l = cerca_ingrediente(wrapper, nome_l)) != NULL) {
			if (ricetta->grammi[j - 1] != 0) {
				j *= 2;
				ricetta->ingredienti = realloc(ricetta->ingredienti, j * sizeof(char *));
				ricetta->grammi = realloc(ricetta->grammi, j * sizeof(int));
			}
			ricetta->ingredienti[i] = _strdup(nome_l);
			printf("Q.ta in grammi: ");
			scanf("%f", &ricetta->grammi[i]);
			// aggiorno il costo e l'apporto calorico
			apporto_cal += (ingrediente_l->app_cal * ricetta->grammi[i]);
			costo += ((ingrediente_l->costo_chilo / (float) 1000) * ricetta->grammi[i]);
		} else {
			printf("Ingrediente non trovato.\n");
			i -= 1;
		}
	}

	// libero memoria
	for (int k = 0; k < i; k++) free(ricetta->ingredienti[k]);
	free(ricetta->ingredienti);
	free(ricetta->grammi);

	printf("*** L'apporto calorico della ricetta e' di %.2f ed essa ha un costo di %.2f. ***\n\n", apporto_cal, costo);
}