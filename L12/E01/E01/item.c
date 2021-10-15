#include "item.h"

Node *newNode(char *strNode, int m, int v) {
	Node *n = malloc(sizeof(Node));
	n->strNode = _strdup(strNode);
	n->m = m; n->v = v; n->visited = 0;
	return n;
}

void freeNode(Node *n) {
	free(n->strNode); free(n);
}