#include "ht.h"

struct ht { Node **datas; int num_data; };

int HThash(char *strNode, int num_nodes) {
	int index = 0, base = 128;
	for (; *strNode != '\0'; strNode++) 
		index = (base * index + *strNode) % num_nodes;
	return index;
}

HT HTinit(int num_nodes) {
	HT ht = malloc(sizeof(*ht));
	ht->num_data = num_nodes;
	ht->datas = malloc(ht->num_data * sizeof(Node*));
	for (int i = 0; i < ht->num_data; i++) {
		if (i == 0) ht->datas[i] = newNode("Ingresso", 0, 0);
		else if (i == num_nodes - 1) ht->datas[i] = newNode("Uscita", 0, 0);
		else ht->datas[i] = NULL;
	}
	return ht;
}

int HTaddData(HT ht, char *strNode, int m, int v) {
	int index = 0;
	if (strcmp(strNode, "Ingresso") == 0) return 0;
	else if (strcmp(strNode, "Uscita") == 0) return ht->num_data - 1;
	else index = HThash(strNode, ht->num_data);
	while (ht->datas[index] != NULL)
		index = (index + 1) % ht->num_data;
	ht->datas[index] = newNode(strNode, m, v);
	return index;
}

int HTfindData(HT ht, char *strNode) {
	int index = 0;
	if (strcmp(strNode, "Ingresso") == 0) return 0;
	else if (strcmp(strNode, "Uscita") == 0) return ht->num_data - 1;
	else index = HThash(strNode, ht->num_data);
	while (strcmp(ht->datas[index]->strNode, strNode) != 0)
		index = (index + 1) % ht->num_data;
	return index;
}

// queste 3 MACRO?!
int HTisDataVisited(HT ht, int index) {
	return ht->datas[index]->visited;
}

void HTchangeVisitedState(HT ht, int index, int vis) {
	ht->datas[index]->visited = vis;
}

Node *HTgetData(HT ht, int index) {
	return ht->datas[index];
}
// -- fine 3

void HTfree(HT ht) {
	for (int i = 0; i < ht->num_data; i++) freeNode(ht->datas[i]);
	free(ht->datas);
	free(ht);
}