#include "pq.h"

struct pqueue { Item *A; int heapsize; };

int LEFT(int i) { return (i * 2 + 1); }
int RIGHT(int i) { return (i * 2 + 2); }
int PARENT(int i) { return ((i - 1) / 2); }

int PQempty(PQ pq) { return (pq->heapsize == 0); }

void Swap(PQ pq, int i, int t) {
	Item tmp = pq->A[t];
	pq->A[t] = pq->A[i];
	pq->A[i] = tmp;
}

PQ PQinit(int n) {
	PQ pq = malloc(sizeof(*pq));
	pq->A = malloc(n * sizeof(Item));
	pq->heapsize = 0;
	return pq;
}

Item PQget(PQ pq) {
	Item item;
	Swap(pq, 0, pq->heapsize - 1);
	item = pq->A[pq->heapsize - 1];
	pq->heapsize--;
	HEAPify(pq, 0);
	return item;
}

void PQinsert(PQ pq, Item item) {
	int i = pq->heapsize++;
	while ((i >= 1) && (ITEMless(pq->A[PARENT(i)], item))) {
		pq->A[i] = pq->A[PARENT(i)];
		i = (i - 1) / 2;
	}
	pq->A[i] = item;
	return;
}

void HEAPify(PQ pq, int i) {
	int l, r, largest;
	l = LEFT(i);
	r = RIGHT(i);
	if ((l < pq->heapsize) && (ITEMgreater(pq->A[l], pq->A[i])))
		largest = l;
	else
		largest = i;
	if ((r < pq->heapsize) && (ITEMgreater(pq->A[r], pq->A[largest])))
		largest = r;
	if (largest != i) {
		Swap(pq, i, largest);
		HEAPify(pq, largest);
	}
	return;
}

void PQfree(PQ pq) {
	for (int i = 0; i < pq->heapsize; i++) ITEMfree(pq->A[i]);
	free(pq->A); free(pq);
}

