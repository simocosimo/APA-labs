#include "item.h"

struct item { char *str; int pr; };

void ITEMshow(Item it) {
	printf("%s - %d\n", it->str, it->pr);
}

Item ITEMnew(char *str, int pr) {
	Item n = malloc(sizeof(*n));
	n->str = _strdup(str); n->pr = pr;
	return n;
}

int ITEMless(Item a, Item b) {
	if (a->pr < b->pr) return 1;
	else return 0;
}

int  ITEMgreater(Item a, Item b) {
	if (a->pr > b->pr) return 1;
	else return 0;
}

void ITEMfree(Item it) {
	free(it->str); free(it);
}