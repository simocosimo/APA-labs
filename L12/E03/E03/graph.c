#include "graph.h"

struct graph { int num_data; int **adjMat; int num_macchine; int U; int posti_macchina; };

int check_posti_macchina(int *sol, int N, int P) {
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++) {
			if (sol[i] == sol[j]) count++;
		}
		if (count > P) return 0;
		else count = 0;
	}
	return 1;
}

void calc_gradimento(int *sol, int N, int K, float *bestU, int *bestSol, int **matrix) {
	int *gradimenti = malloc(K * sizeof(int));
	float tot_grad = 0;
	for (int i = 0; i < K; i++) gradimenti[i] = 0;
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < N; j++) {
			if (sol[j] == i) {
				for (int k = j + 1; k < N; k++)
					if (sol[k] == sol[j]) gradimenti[i] += matrix[j][k];
			}
		}
	}
	for (int i = 0; i < K; i++) tot_grad += (float)gradimenti[i];
	tot_grad /= K;

	// controllo se il gradimento toale � maggiore del bestU
	if (tot_grad > *bestU) {
		*bestU = tot_grad;
		for (int i = 0; i < N; i++) bestSol[i] = sol[i];
	}
	free(gradimenti);
}

void algoritmo_er(int pos, int N, int m, int K, int P, float *bestU, int *bestSol, int *sol, int **matrix) {
	// terminazione
	if (pos >= N) {
		if (m == K) {
			if (check_posti_macchina(sol, N, P)) {
				calc_gradimento(sol, N, K, bestU, bestSol, matrix); // modifica bestU e bestSol solo se tmpU da sol > bestU;
			}
		}
		return;
	}

	for (int i = 0; i < m; i++) {
		sol[pos] = i;
		algoritmo_er(pos + 1, N, m, K, P, bestU, bestSol, sol, matrix);
	}
	sol[pos] = m;
	algoritmo_er(pos + 1, N, m + 1, K, P, bestU, bestSol, sol, matrix);
}

GRAPH GRAPHinit(int num_nodes, int macchine, int posti_m) {
	GRAPH g = malloc(sizeof(*g));
	g->num_data = num_nodes;
	g->num_macchine = macchine;
	g->posti_macchina = posti_m;
	g->adjMat = malloc(g->num_data * sizeof(int*));
	for (int i = 0; i < g->num_data; i++) 
		g->adjMat[i] = malloc(g->num_data * sizeof(int*));

	for (int i = 0; i < g->num_data; i++) 
		for (int j = 0; j < g->num_data; j++)
			g->adjMat[i][j] = 0;
	return g;
}

GRAPH GRAPHinitFromFile(char *filename) {
	FILE *fp = fopen(filename, "r");
	if (!fp) return NULL;
	GRAPH g;
	int num_nodes, macchine, posti_m;

	fscanf(fp, "%d %d %d\n", &num_nodes, &macchine, &posti_m);
	g = GRAPHinit(num_nodes, macchine, posti_m);

	for (int i = 0; i < g->num_data; i++) {
		for (int j = 0; j < g->num_data; j++) {
			fscanf(fp, "%d", &g->adjMat[i][j]);
		}
	}

	return g;
}

void er_wrapper(GRAPH g) {
	int *sol = malloc(g->num_data * sizeof(int));
	int *bestSol = malloc(g->num_data * sizeof(int));
	for (int i = 0; i < g->num_data; i++) {
		sol[i] = -1; bestSol[i] = -1;
	}
	float bestU = 0;

	algoritmo_er(0, g->num_data, 0, g->num_macchine, g->posti_macchina, &bestU, bestSol, sol, g->adjMat);

	printf("Migliore composizione macchine:\n");
	for (int i = 0; i < g->num_macchine; i++) {
		printf("-Macchina %d:\n", i + 1);
		for (int j = 0; j < g->num_data; j++) {
			if(bestSol[j] == i)
				printf("\tAmico %d\n", j);
		}
	}
	printf("Gradimento massimo medio: %.2f\n", bestU);
	free(sol); free(bestSol);
}

void GRAPHfree(GRAPH g) {
	for (int i = 0; i < g->num_data; i++) free(g->adjMat[i]);
	free(g->adjMat);
	free(g);
}