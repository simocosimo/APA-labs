#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LCOD 10
#define MAXD 11
#define MAXS 26

typedef enum comandi
{
	c_stampa, c_sPrezzo, c_sCod, c_sNome, c_pCat, c_canc, c_add, c_fine
} cmd_e;

typedef struct prodotto
{
	char codProdotto[LCOD];
	char *nome, *cat;
	float prezzo;
	int nDisp;
	int cancellato;
	char data[MAXD];
} prodotto_t;

int leggiCatalogo(prodotto_t **arrayP, prodotto_t ***sortPrezzo, prodotto_t ***sortNome, prodotto_t ***sortCod);
void eseguiComando(prodotto_t **arrayP, prodotto_t ***sortPrezzo, prodotto_t ***sortNome, prodotto_t ***sortCod, int *n, cmd_e scelta, int *fine);
void liberaMemoria(prodotto_t *arrayP, int n);

void stampaCatalogo(prodotto_t *arrayP, int n);
void stampaPerCat(prodotto_t *arrayP, int n);
void selSort(prodotto_t *arrayP, prodotto_t ***sortArray, int n, int toSort);
void aggiungiProdotto(prodotto_t **arrayP, prodotto_t ***sortPrezzo, prodotto_t ***sortNome, prodotto_t ***sortCod, int *n);
void cancellaProdotto(prodotto_t **arrayP, int n);

int main(int argc, char **argv)
{
	prodotto_t *arrayProdotti = NULL;

	// array di sort
	prodotto_t **sortPrezzo = NULL;
	prodotto_t **sortNome = NULL;
	prodotto_t **sortCod = NULL;

	int fine = 0, scelta;
	int n = leggiCatalogo(&arrayProdotti, &sortPrezzo, &sortNome, &sortCod);
	if (n == -1) return -1;

	while (!fine) {
		printf("Menu:\n1)Stampa catalogo.\n");
		printf("2)Ordina catalogo per prezzo.\n");
		printf("3)Ordina catalogo per codice prodotto.\n");
		printf("4)Ordina catalogo per nome prodotto.\n");
		printf("5)Stampa prodotti per categoria.\n");
		printf("6)Aggiungi prodotto.\n");
		printf("7)Elimina un prodotto.\n");
		printf("8)Fine.\nScelta: ");
		scanf("%d", &scelta);
		eseguiComando(&arrayProdotti, &sortPrezzo, &sortNome, &sortCod, &n, (cmd_e)scelta, &fine);
	}

	liberaMemoria(arrayProdotti, n);
	return 0;
}

int leggiCatalogo(prodotto_t **arrayP, prodotto_t ***sortPrezzo, prodotto_t ***sortNome, prodotto_t ***sortCod)
{
	FILE *fp;
	int n;
	char nome[MAXS], cat[MAXS];

	if (!(fp = fopen("catalogo.txt", "r")))
		return -1;

	fscanf(fp, "%d\n", &n);
	if (n < 0) return -1;

	// alloco la memoria per l'array di struct e per l'array di puntatori a struct
	(*arrayP) = malloc(n * sizeof(prodotto_t));
	(*sortPrezzo) = malloc(n * sizeof(prodotto_t*));
	(*sortCod) = malloc(n * sizeof(prodotto_t*));
	(*sortNome) = malloc(n * sizeof(prodotto_t*));

	// riempio l'array 
	for (int i = 0; i < n; i++) {
		fscanf(fp, "%s%s%s%f%d%s", (*arrayP)[i].codProdotto, nome, cat, &(*arrayP)[i].prezzo, &(*arrayP)[i].nDisp, (*arrayP)[i].data);
		(*arrayP)[i].cancellato = 0;
		//alloco dinamicamente i campi stringa della struct, nel caso fossero più corte dei 25 caratteri 
		(*arrayP)[i].nome = malloc(strlen(nome) * sizeof(char));
		(*arrayP)[i].cat = malloc(strlen(cat) * sizeof(char));
	}

	// chiudo il file
	fclose(fp);
	return n;
}

void eseguiComando(prodotto_t **arrayP, prodotto_t ***sortPrezzo, prodotto_t ***sortNome, prodotto_t ***sortCod, int *n, cmd_e scelta, int *fine)
{
	switch (scelta)
	{
	case c_stampa:
		stampaCatalogo(*arrayP, *n);
		break;

	case c_pCat:
		stampaPerCat(*arrayP, *n);
		break;

	case c_sPrezzo:
		selSort(*arrayP, sortPrezzo, *n, 0);
		break;

	case c_sNome:
		selSort(*arrayP, sortNome, *n, 1);
		break;

	case c_sCod:
		selSort(*arrayP, sortCod, *n, 2);
		break;

	case c_add:
		aggiungiProdotto(arrayP, sortPrezzo, sortNome, sortCod, n);
		break;

	case c_canc:
		cancellaProdotto(arrayP, *n);
		break;

	case c_fine:
		*fine = 1;
		break;
	}
}

void stampaCatalogo(prodotto_t *arrayP, int n)
{
	FILE *fp;
	int s;

	printf("*** Stampa catalogo:\n1) Stampa su file.\n2) Stampa su schermo.\nScelta: ");
	scanf("%d", &s);
	if (s == 1) {
		fp = fopen("outputCatalogo.txt", "w");
		for (int i = 0; i < n; i++) {
			if (arrayP[i].cancellato != 1) {
				fprintf(fp, "%s %s %s %f %d %s\n", arrayP[i].codProdotto, arrayP[i].nome, arrayP[i].cat, arrayP[i].prezzo, arrayP[i].nDisp, arrayP[i].data);
			}
		}
		fclose(fp);
	} else if (s == 2) {
		for (int i = 0; i < n; i++) {
			if (arrayP[i].cancellato != 1) {
				fprintf(stdout, "%s %s %s %f %d %s\n", arrayP[i].codProdotto, arrayP[i].nome, arrayP[i].cat, arrayP[i].prezzo, arrayP[i].nDisp, arrayP[i].data);
			}
		}
	}
}

void selSort(prodotto_t *arrayP, prodotto_t ***sortArray, int n, int toSort)
{
	int min;
	for (int i = 0; i < n; i++) {
		min = i;
		for (int j = i + 1; j <= n; j++) {
			if (toSort == 0) {
				if (arrayP[j].prezzo < arrayP[i].prezzo) min = j;
			} else if (toSort == 1) {
				if (strcmp(arrayP[j].nome, arrayP[i].nome) < 0) min = j;
			} else if (toSort == 2) {
				if (strcmp(arrayP[j].codProdotto, arrayP[i].codProdotto) < 0) min = j;
			}
		}
		(*sortArray)[i] = &(arrayP[min]);
	}
}

void stampaPerCat(prodotto_t *arrayP, int n)
{
	int *stampati = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) stampati[i] = 0;

	for (int i = 0; i < n; i++) {
		if (stampati[i] != 1) {
			printf("Categoria: %s\n", arrayP[i].cat);
			for (int j = i; j < n; j++) {
				if (strcmp(arrayP[j].cat, arrayP[i].cat) == 0) {
					if (arrayP[j].cancellato != 1) {
						printf("\t- %s %s %f %d %s\n", arrayP[i].codProdotto, arrayP[i].nome, arrayP[i].prezzo, arrayP[i].nDisp, arrayP[i].data);
						stampati[i] = 1;
					}
				}
			} printf("\n\n");
		}
	}

}

void aggiungiProdotto(prodotto_t **arrayP, prodotto_t ***sortPrezzo, prodotto_t ***sortNome, prodotto_t ***sortCod, int *n)
{
	prodotto_t nuovo;
	int inserito = 0;
	FILE *fp;

	fp = fopen("catalogo.txt", "w");

	printf("Inserisci i dati del nuovo prodotto (Codice, nome, categoria, prezzo, n. disponibili, data): ");
	fscanf(stdin, "%s%s%s%f%d%s", nuovo.codProdotto, nuovo.nome, nuovo.cat, &nuovo.prezzo, &nuovo.nDisp, nuovo.data);
	fscanf(fp, "%s%s%s%f%d%s", nuovo.codProdotto, nuovo.nome, nuovo.cat, &nuovo.prezzo, &nuovo.nDisp, nuovo.data);
	nuovo.cancellato = 0;

	// controllo se il vettore è pieno, se non lo è rialloco 
	if ((*sortPrezzo)[*n-1] != NULL && (*sortNome)[*n - 1] != NULL && (*sortCod)[*n - 1] != NULL) {
		(*arrayP) = realloc(arrayP, (*n) * 2 * sizeof(prodotto_t));
		(*sortPrezzo) = realloc(sortPrezzo, (*n) * 2 * sizeof(prodotto_t*));
		(*sortNome) = realloc(sortNome, (*n) * 2 * sizeof(prodotto_t*));
		(*sortCod) = realloc(sortCod, (*n) * 2 * sizeof(prodotto_t*));
	}
	(*arrayP)[*n] = nuovo;
	(*n)++;

	// aggiungo tutto agli array ordinati quindi
	// Prezzo 
	for (int i = 0; i < *n; i++) {
		if (nuovo.prezzo < (*(*sortPrezzo)[i]).prezzo) {
			for (int j = *n - 2; j >= i; j--) {
				(*sortPrezzo)[j + 1] = (*sortPrezzo)[j];
			}
			(*sortPrezzo)[i] = &((*arrayP)[*n - 1]); inserito = 1;
		}
	}

	if(!inserito) (*sortPrezzo)[*n - 1] = &((*arrayP)[*n - 1]);
	inserito = 0;

	// Nome
	for (int i = 0; i < *n; i++) {
		if (strcmp(nuovo.nome, (*(*sortNome)[i]).nome) < 0) {
			for (int j = *n - 2; j >= i; j--) {
				(*sortNome)[j + 1] = (*sortNome)[j];
			}
			(*sortNome)[i] = &((*arrayP)[*n - 1]); inserito = 1;
		}
	}

	if (!inserito) (*sortNome)[*n - 1] = &((*arrayP)[*n - 1]);
	inserito = 0;

	// Codice
	for (int i = 0; i < *n; i++) {
		if (strcmp(nuovo.codProdotto, (*(*sortCod)[i]).codProdotto) < 0) {
			for (int j = *n - 2; j >= i; j--) {
				(*sortCod)[j + 1] = (*sortCod)[j];
			}
			(*sortCod)[i] = &((*arrayP)[*n - 1]); inserito = 1;
		}
	}

	if (!inserito) (*sortCod)[*n - 1] = &((*arrayP)[*n - 1]);
	inserito = 0;
 
}

void cancellaProdotto(prodotto_t **arrayP, int n)
{
	char prd[MAXS];
	printf("Inserisci il codice del prodotto da cancellare: ");
	scanf("%s", prd);
	for (int i = 0; i < n; i++) {
		if (strcmp((*arrayP)[i].nome, prd) == 0) (*arrayP)[i].cancellato = 1;
	}
}

void liberaMemoria(prodotto_t *arrayP, int n)
{
	// liberare array di sort
	for (int i = 0; i < n; i++) {
		free(arrayP[i].nome);
		free(arrayP[i].cat);
	}
	free(arrayP);
}