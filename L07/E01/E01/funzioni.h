#pragma once
#ifndef _FUNZ_H_
#define _FUNZ_H_

#include <stdio.h>
#include <stdlib.h>

#define MAXC 10
#define NUMU 9

int cover(int ***s, int *n, int *k);
void sumset(int pos, int *s[MAXC], int *sol, int *u, int x, int n, int k);
int check(int *u, int **s, int *sol, int n);

#endif