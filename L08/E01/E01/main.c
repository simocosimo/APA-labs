#include <stdio.h>
#include <stdlib.h>

int esamina(int *arr, int dim, int start);
int scambia(int *arr, int sx, int dx, int start);

int main(int argc, char **argv)
{
	int *arr;
	int n_scambi, n_frecce;

	printf("Inserisci il numero di frecce seguite da 0/1: ");
	scanf("%d", &n_frecce);
	arr = malloc((n_frecce + 1) * sizeof(int));
	for (int i = 0; i < n_frecce; i++) scanf("%d", &arr[i]);

	n_scambi = esamina(arr, n_frecce, 0);
	printf("Numero totale di scambi: %d\n", n_scambi);

	free(arr);
	system("PAUSE");
	return 0;
}

int esamina(int *arr, int dim, int start) {

	int i = 0, j = 0, sx = 1, dx = 1, scambi = 0;
	if (dim != 0) {
		for (; arr[i] == arr[i + 1] && i < dim - 1; i++, sx++);
		for (j = i + 1; arr[j] == arr[j + 1] && j < dim - 1; j++, dx++);
		if (sx != dx) scambi += scambia(arr, sx, dx, start);
		scambi += esamina(arr + dx + sx, dim - sx - dx, sx + dx);
	}
	return scambi;
}

int scambia(int *arr, int sx, int dx, int start) {

	int diff = 0, cnt = 0;
	if (sx > dx) {
		diff = sx - dx; 
		for (int i = 1; i <= diff / 2; i++) {
			arr[start + sx - i] = 1; cnt++;
			printf("Scambio 0 -> 1 in posizione %d.\n", start + sx - i);
		}
	} else if (dx > sx) {
		diff = dx - sx;
		for (int i = 1; i <= diff / 2; i++) {
			arr[start + i] = 0; cnt++;
			printf("Scambio 1 -> 0 in posizione %d.\n", start + i);
		}
	}
	return cnt;
}