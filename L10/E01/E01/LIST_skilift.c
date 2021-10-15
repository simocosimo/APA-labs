#include "LIST_skilift.h"

List *createList() {
	List *l = malloc(sizeof(*l));
	l->head = l->tail = NULL;
	return l;
}

Node *newNode(char *skiliftID, int ti_mins) {
	Node *n = malloc(sizeof(*n));
	n->skiliftID = _strdup(skiliftID);
	n->ti_mins = ti_mins;
	n->next = NULL;
	return n;
}

void addNodeToList(List *list, char *skiliftID, int ti_mins) {
	if (list->head == NULL) {
		list->head = list->tail = newNode(skiliftID, ti_mins);
	} else {
		list->tail->next = newNode(skiliftID, ti_mins);
		list->tail = list->tail->next;
	}
}

int getTiMins(List *list, char *skiliftID) {
	Node *s;
	for (s = list->head; s != NULL; s = s->next) {
		if (strcmp(skiliftID, s->skiliftID) == 0) return s->ti_mins;
	}
	return -1;
}

void modifyNode(List *list, char *skiliftID, int time) {
	Node *s;
	for (s = list->head; s != NULL; s = s->next) {
		if (strcmp(skiliftID, s->skiliftID) == 0) s->ti_mins = time;
	}
}

List *readSkiliftsFromFile(char *filename) {
	List *l = createList();
	FILE *fp = fopen(filename, "r");
	int to_read, ti;
	char skiliftID[MAXSKILID];
	if (!fp) return NULL;
	fscanf(fp, "%d\n", &to_read);
	for (int i = 0; i < to_read; i++) {
		fscanf(fp, "%s %d\n", skiliftID, &ti);
		addNodeToList(l, skiliftID, ti);
	}
	fclose(fp);
	return l;
}

void freeNode(Node *node) {
	free(node->skiliftID);
	free(node);
}

void freeList(List *list) {
	if (list->head == NULL) {
		free(list); return;
	}
	Node *t;
	t = list->head;
	list->head = list->head->next;
	freeNode(t); freeList(list);
}