#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo* link;

typedef struct nodo {
	char *str;
	link next;
}nodo;

link splitStringa(char *str, char sep);
link nuovaSubStr(char *substr, int i);
void stampaLista(link h);
void liberaLista(link h);


int main(int argc, char **argv)
{
	link h;
	char *stringa = "aaaa.bbb.cc.d";
	char sep = '.';

	h = splitStringa(stringa, sep);
	stampaLista(h);
	liberaLista(h);

	return 0;
}

link splitStringa(char *str, char sep)
{
	link h;
	int i = 0;

	for (; (i < strlen(str)) && (str[i] != sep); i++);
	
	// impedisco di allocare nodi con stringhe vuote
	if (i == 0) 
		return (i != strlen(str)) ? splitStringa(str + i + 1, sep) : NULL;

	h = nuovaSubStr(str, i);
	h->next = (i == strlen(str)) ? NULL : splitStringa(str + i + 1, sep);
	return h;
}

link nuovaSubStr(char *substr, int i)
{
	link n = malloc(sizeof(*n));
	n->str = malloc(i * sizeof(char) + 1);
	strncpy(n->str, substr, i);
	n->str[i] = '\0';
	n->next = NULL;
	return n;
}

void stampaLista(link h)
{
	if(h == NULL) return;
	printf("%s\n", h->str);
	stampaLista(h->next);
}

void liberaLista(link h)
{
	if (h == NULL) return;
	liberaLista(h->next);
	free(h->str);
	free(h);
}