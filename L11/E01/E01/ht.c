#include "ht.h"

// ADT
struct ht { Node **nodes; int num_data; };
int HThash(char*, int);

Node *newNode(char *strNode, char *strSubNet) {
	Node *n = malloc(sizeof(Node));
	n->strNode = _strdup(strNode);
	n->strSubNet = _strdup(strSubNet);
	return n;
}

HT HTInit(int num_data)
{
	HT ht;
	ht = malloc(sizeof(*ht));
	ht->nodes = malloc(num_data * sizeof(Node*));
	for (int i = 0; i < num_data; i++) 
		ht->nodes[i] = NULL;
	ht->num_data = num_data;
	return ht;
}

int HThash(char *str, int num_data) {
	int index = 0, base = 128;
	for (; *str != '\0'; str++) 
		index = (base * index + *str) % num_data;
	return index;
}

int HTaddData(HT ht, char *strNode, char *strSubNet) {
	if (ht == NULL) return -1;
	int index = HThash(strNode, ht->num_data);
	while (ht->nodes[index] != NULL)
		index = (index + 1) % ht->num_data;
	ht->nodes[index] = newNode(strNode, strSubNet);
	return index;
}

int HTfindData(HT ht, char *strNode) {
	if (ht == NULL) return -1;
	int index = HThash(strNode, ht->num_data);
	while (strcmp(ht->nodes[index]->strNode, strNode) != 0)
		index = (index + 1) % ht->num_data;
	return index;
}

Node *HTgetData(HT ht, int index) {
	if (ht == NULL) return NULL;
	if (index < ht->num_data && index >= 0) return ht->nodes[index];
	return NULL;
}

void Nodefree(Node *n) {
	free(n->strNode);
	free(n->strSubNet);
	free(n);
}

void HTfree(HT ht) {
	for (int i = 0; i < ht->num_data; i++) {
		Nodefree(ht->nodes[i]);
	}
	free(ht->nodes); 
	free(ht);
}