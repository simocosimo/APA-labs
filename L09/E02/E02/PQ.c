#include "PQ.h"

typedef struct queuenode QUEUEnode;

static int nPlayers = 0;

struct queuenode {
	Item val;
	QUEUEnode *next;
};

static QUEUEnode *head, *tail;

QUEUEnode *NewPlayer(Item it, QUEUEnode *next) {
	
	QUEUEnode *x = malloc(sizeof(*x));
	x->val = it;
	x->next = next;
	return x;
}

void QUEUEput(Item it) {
	if (isQUEUEempty()) {
		head = (tail = NewPlayer(it, head));
		nPlayers++;
		return;
	}
	tail->next = NewPlayer(it, tail->next);
	tail = tail->next;
	nPlayers++;
}

Item QUEUEfindmin() {

	QUEUEnode *x;
	Item min = head->val;
	Item r;

	for (x = head->next; x != NULL; x = x->next) {
		if (x->val.score < min.score) {
			min = x->val;
		}
	}

	r = QUEUEextract(min.id);
	return r;
}

Item QUEUEextract(int id) {

	QUEUEnode *x = head, *s = head->next, *t = NULL;
	Item r;
	r.score = 0;

	if (isQUEUEempty()) return r;
	
	// estrazione in testa
	if (x->val.id == id) { 
		t = x;
		r = t->val;
		free(head);
		head = s;
		nPlayers--;
		return r;
	}

	// non in testa
	for (; s != NULL && (s->val.id != id); x = s, s = s->next);
	t = s;
	x->next = s->next;
	r = t->val;
	if (t == tail) tail = x;
	free(t);
	nPlayers--;
	return r;
}

void QUEUEmatch() {

	Item min1, min2;
	min1 = QUEUEfindmin();
	min2 = QUEUEfindmin();

	int winner = RandomResults();
	SetPoints(min1, min2, winner);

}

void QUEUEinit() { head = tail = NULL; }

int isQUEUEempty() { return (head == NULL); }

int RandomResults() {
	// genero 1 o 0 casualmente, considero quello che esce come vittoria/sconfitta del primo giocatore
	// quindi se 1 -> giocatore 1 vincente
	// se 0 -> giocatore 1 perdente
	// così evito pareggi
	int R = (rand() < RAND_MAX / 2); // SOSTITUIRE CON SRAND
	if (R == 1) return 1;
	else return 2;
}

void QUEUEprint() {

	QUEUEnode *x;
	if (isQUEUEempty()) printf("Empty Queue.\n");
	else for (x = head; x != NULL; x = x->next) PrintItem(x->val);
	return;
}

void QUEUEread_file() {

	FILE *fp = fopen("giocatori.txt", "r");
	Item r;
	int n;

	QUEUEfree();
	fscanf(fp, "%d\n", &n);
	nPlayers = n;
	for (int i = 0; i < n; i++) {
		fscanf(fp, "%d\t%f\n", &r.id, &r.score);
		if (r.id > getStaticId()) updateStaticId(r.id + 1);
		QUEUEput(r);
	}
	fclose(fp);
}

void QUEUEsave_file() {

	FILE *fp = fopen("giocatori.txt", "w");
	QUEUEnode *x;

	if (isQUEUEempty()) return;

	fprintf(fp, "%d\n", nPlayers);
	for (x = head; x != NULL; x = x->next) {
		fprintf(fp, "%d\t%.2f\n", x->val.id, x->val.score);
	}
	fclose(fp);
}

void SetPoints(Item it1, Item it2, int winner) {

	if (winner == 1) {
		it1.score += ((float)25 / 100) * it2.score;
		it2.score -= ((float)25 / 100) * it2.score;
	}
	else {
		it2.score += ((float)25 / 100) * it1.score;
		it1.score -= ((float)25 / 100) * it1.score;
	}

	if (it1.score > 0) QUEUEput(it1);
	else printf("Giocatore (id: %d) eliminato (punteggio = 0).\n", it1.id);

	if (it2.score > 0) QUEUEput(it2);
	else printf("Giocatore (id: %d) eliminato (punteggio = 0).\n", it2.id);
	return;
}

void QUEUEfree() {

	QUEUEnode *x;
	if (head == NULL) {
		QUEUEinit(); return;
	}
	x = head;
	head = head->next;
	free(x);
	QUEUEfree();
}