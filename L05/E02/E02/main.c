#include <stdio.h>

int converti(int a, int b);

int main(int argc, char **argv)
{
	int a, b;
	printf("Inserisci il numero e la base in cui convertirlo: ");
	scanf("%d%d", &a, &b);

	converti(a, b);
	printf("\n");

	return 0;
}

int converti(int a, int b)
{
	if (a != 0) {
		converti(a / b, b);
		printf("%d", a % b);
	}
}