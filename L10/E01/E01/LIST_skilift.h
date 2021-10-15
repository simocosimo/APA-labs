#ifndef _LIST_SKILIFT_H_
#define _LIST_SKILIFT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSKILID 11

typedef struct node Node;
typedef struct list List;

struct node {
	char *skiliftID;
	int ti_mins;
	Node *next;
};

struct list {
	Node *head, *tail;
};

List *createList();
Node *newNode(char *skiliftID, int ti_mins);
void addNodeToList(List *list, char *skiliftID, int ti_mins);
int getTiMins(List *list, char *skiliftID);
void modifyNode(List *list, char *skiliftID, int time);
List *readSkiliftsFromFile(char *filename);
// free functions
void freeList(List *list);
void freeNode(Node *node);

#endif