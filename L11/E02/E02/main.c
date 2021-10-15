#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "pq.h"

#define MAXN 10

int main(int argc, char **argv) {

	PQ pq = PQinit(MAXN);

	PQinsert(pq, ITEMnew("ciao", 4));
	PQinsert(pq, ITEMnew("come", 7));
	PQinsert(pq, ITEMnew("va?", 5));

	while (!PQempty(pq)) {
		Item a = PQget(pq);
		ITEMshow(a);
		ITEMfree(a);
	}

	PQfree(pq);
	system("PAUSE");
	return 0;
}
