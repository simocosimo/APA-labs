#pragma once
#ifndef _INGREDIENTI_H_
#define _INGREDIENTI_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 255

typedef struct ingrediente ingrediente_t;
typedef struct ingredienti ingredienti_w;

struct ingrediente{
	char nome[MAXC];
	float costo_chilo;
	float app_cal;
	ingrediente_t *next;
};

struct ingredienti{
	ingrediente_t *head;
	ingrediente_t *tail;
};

ingredienti_w *leggi_ingredienti();
ingrediente_t *nuovo_ingrediente(ingrediente_t *tmp);
ingrediente_t *cerca_ingrediente(ingredienti_w *wrapper, char nome[MAXC]);
void libera_ingredienti(ingredienti_w *wrapper);

#endif