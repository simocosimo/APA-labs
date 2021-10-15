#ifndef _PQ_H_
#define _PQ_H_

#include "item.h"
#include <time.h>
#include <stdio.h>

void QUEUEput(float score);
Item QUEUEfindmin();
Item QUEUEextract(int id);
void QUEUEmatch();
void QUEUEinit();
int isQUEUEempty();
void QUEUEput(Item it);
int RandomResults();
void QUEUEprint();
void QUEUEread_file();
void QUEUEsave_file();
void SetPoints(Item it1, Item it2, int winner);
void QUEUEfree();

#endif