#include "item.h"

static int id = 0;

Item NewItem(float score) {

	Item r;
	r.score = score;
	r.id = id++;
	return r;
}

void PrintItem(Item val) {
	printf("Id: %d\tScore: %.2f\n", val.id, val.score);
}

int getStaticId() { return id - 1; }

void updateStaticId(int n) { id = n; }