#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXS 11 /* 10 + 1 per '\0' */

// Definizione delle strutture dati usate
typedef struct nodo* link;

struct nodo {
	char val[MAXS];
	link left;
	link right;
};

// Prototipi delle funzioni di utilità
link new_nodo(char *val);
link leggi_nodo(FILE *in);
link leggi_albero(char *filename);
void libera_albero(link root);
void display_albero(link root);

// Prototipi delle funzioni da implementare
int distanza(link n, char *k1, char *k2);
int contaCompleti(link n, int L1, int L2);

int main(int argc, char **argv) {
	link root;
	root = leggi_albero(argv[1]);
	display_albero(root);

	// invocazione delle funzioni richieste
	int a, b;
	scanf("%d%d", &a, &b);
	printf("%d\n", contaCompleti(root, a, b));

	libera_albero(root);
	system("PAUSE");
	return 0;
}

// Implementazione delle funzioni di utilità

link new_nodo(char *val) {
	link n = malloc(1 * sizeof(*n));
	strcpy(n->val, val);
	n->left = NULL;
	n->right = NULL;
	return n;
};


void display_albero(link root) {
	if (root == NULL) return;
	printf("nodo %s\n", root->val);
	display_albero(root->left);
	display_albero(root->right);
}

void libera_albero(link root) {
	if (root == NULL) return;
	libera_albero(root->left);
	libera_albero(root->right);
	free(root);
}

link leggi_nodo(FILE *in) {
	char val[MAXS];
	int l, r;
	if (fscanf(in, "%s %d %d", val, &l, &r) != 3) return NULL;
	link n = new_nodo(val);
	if (l != 0) n->left = leggi_nodo(in);
	if (r != 0) n->right = leggi_nodo(in);
	return n;
}

link leggi_albero(char *filename) {
	FILE *in;
	in = fopen(filename, "r");
	link root = leggi_nodo(in);
	fclose(in);
	return root;
}

// Implementazione delle funzioni da aggiungere
int distanza(link n, char *k1, char *k2) 
{
	return 0;
}


int contaCompleti(link n, int L1, int L2) {
	
	int cnt = 0;

	if (L1 != 0) {
		cnt += contaCompleti(n->left, L1 - 1, L2 - 1) + contaCompleti(n->right, L1 - 1, L2 - 1);
	} else if (L2 == L1 || n == NULL) {
		return cnt;
	} else {
		if (n->left != NULL && n->right != NULL) cnt += 1;
		cnt += contaCompleti(n->left, 0, L2 - 1);
		cnt += contaCompleti(n->right, 0, L2 - 1);
	} 

	return cnt;
}
