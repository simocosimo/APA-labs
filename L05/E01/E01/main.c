#include <stdio.h>

int Hof(int n);

int main(int argc, char **argv)
{
	int n;
	printf("Inserisci un numero: ");
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) printf("%d ", Hof(i));

	return 0;
}

int Hof(int n)
{
	if (n == 1 || n == 2) return 1;
	return Hof(n - Hof(n - 1)) + Hof(n - Hof(n - 2));
}