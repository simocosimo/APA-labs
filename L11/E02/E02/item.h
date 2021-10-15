#ifndef ITEM_H_DEFINED
#define ITEM_H_DEFINED

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct item *Item;

void ITEMshow(Item);
Item ITEMnew(char *, int);
int  ITEMless(Item, Item);
void ITEMfree(Item);
int  ITEMgreater(Item, Item);

#endif
