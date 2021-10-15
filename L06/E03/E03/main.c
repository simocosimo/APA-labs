#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct punto* link;

typedef struct punto
{
	int x, y;
	link next;
} nodo;

link nuovoNodo(int x, int y, link next);
float calcDist(int x, int y);
void prendiPunto(link *h, int *fine);
void stampaLista(link h);
void liberaLista(link h); 

int main(int argc, char **argv)
{
	link h = NULL;
	int fine = 0;

	while(!fine) prendiPunto(&h, &fine);

	return 0;
}

void prendiPunto(link *h, int *fine)
{
	link s, p;
	int x, y;
	float d;

	printf("Inserisci le coordinate di un punto (inserire una lettera per uscire): ");
	if (!scanf("%d%d", &x, &y)) { 
		liberaLista((*h));
		*fine = 1;
		return;
	}

	d = calcDist(x, y);
	if ((*h) == NULL) {
		(*h) = nuovoNodo(x, y, NULL);
	} else {
		if (d <= calcDist((*h)->x, (*h)->y)) (*h) = nuovoNodo(x, y, (*h));
		else {
			for (s = (*h)->next, p = (*h); (s != NULL) && (d >= calcDist(s->x, s->y)); p = s, s = s->next);
			p->next = nuovoNodo(x, y, s);
		}
	}

	stampaLista((*h));
	return;
}

link nuovoNodo(int x, int y, link next)
{
	link n = malloc(sizeof(*n));
	n->next = next; 
	n->x = x; n->y = y;
	return n;
}

float calcDist(int x, int y)
{
	return sqrt((x*x) + (y*y));
}

void stampaLista(link h)
{
	if (h == NULL) return;
	printf("x: %d -  y: %d\n", h->x, h->y);
	stampaLista(h->next);
}

void liberaLista(link h)
{
	if (h == NULL) return;
	liberaLista(h->next);
	free(h);
}