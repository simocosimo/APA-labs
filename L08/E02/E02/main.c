#include "ricette.h"

void menu(int *stop, ricette_w *ricette, ingrediente_t *ingredienti, int n_ingredienti);

int main(int argc, char **argv)
{
	ingrediente_t *ingredienti_file;
	ricette_w *ricette_file;
	int stop = 0, n_ingredienti = 0;

	n_ingredienti = leggi_ingredienti_file(&ingredienti_file);
	ricette_file = leggi_ricette();
	while(!stop) menu(&stop, ricette_file, ingredienti_file, n_ingredienti);

	libera_ricette(ricette_file);
	system("PAUSE");
	return 0;
}

void menu(int *stop, ricette_w *ricette, ingrediente_t *ingredienti, int n_ingredienti) {

	int scelta;

	printf("Menu:\n");
	printf("1) Stampa dettagli di una ricetta.\n");
	printf("2) Stampa dettagli di un ingrediente.\n");
	printf("3) Calcolo costo di una ricetta.\n");
	printf("4) Calcolo apporto calorico di una ricetta.\n");
	printf("5) Stampa elenco ricette.\n");
	printf("6) Stampa elenco ingredienti.\n");
	printf("7) Stampa elenco ricette che utilizzano un determinato ingrediente.\n");
	printf("8) Inserimento di una nuova ricetta.\n");
	printf("9) Fine.\n");
	scanf("%d", &scelta);

	switch (scelta)
	{
	case 1:
		stampa_ricetta_nome(ricette);
		break;

	case 2:
		stampa_ingrediente(ingredienti, n_ingredienti);
		break;

	case 3:
		costo_ricetta(ricette, ingredienti, n_ingredienti);
		break;


	case 4:
		app_cal_ricetta(ricette, ingredienti, n_ingredienti);
		break;

	case 5:
		stampa_ricette(ricette);
		break;

	case 6:
		stampa_ingredienti(ingredienti, n_ingredienti);
		break;

	case 7:
		stampa_ricetta_ingr(ricette);
		break;

	case 8:
		nuova_ricetta_input(ricette, ingredienti, n_ingredienti);
		break;

	case 9:
		*stop = 1;
		break;

	default:
		break;
	}
}
