#include "PQ.h"

void menu(int *fine);

int main(int argc, char **argv)
{
	int fine = 0;
	QUEUEinit();

	while (!fine) menu(&fine);

	return 0;
}

void menu(int *fine) {

	int scelta, id;
	Item it;

	printf("\nMenu:\n");
	printf("1) Stampa l'attuale classifica.\n");
	printf("2) Inserisci un nuovo partecipante.\n");
	printf("3) Elimina un partecipante.\n");
	printf("4) Simula partita.\n");
	printf("5) Carica classifica da file.\n");
	printf("6) Salva classifica su file.\n");
	printf("7) fine.\n");
	scanf("%d", &scelta);

	switch (scelta)
	{
	case 1: QUEUEprint(); break;
	case 2: it = NewItem(10); QUEUEput(it); printf("Giocatore con id:%d aggiunto.\n", getStaticId()); break;
	case 3: 
		printf("Inserisci l'id del giocatore da eleminare: ");
		scanf("%d", &id);
		QUEUEextract(id);
		break;
	case 4:	QUEUEmatch(); break;
	case 5: QUEUEread_file(); break;
	case 6: QUEUEsave_file(); break;
	case 7: QUEUEfree(); *fine = 1; break;
	default: break;
	}

}