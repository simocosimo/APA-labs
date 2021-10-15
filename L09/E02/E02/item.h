#ifndef _ITEM_H_
#define _ITEM_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct item Item;

struct item {
	float score;
	int id;
};

Item NewItem(float punti);
void PrintItem(Item val);
void SetPoints(Item it1, Item it2, int winner);
int getStaticId();
void updateStaticId(int n);

#endif