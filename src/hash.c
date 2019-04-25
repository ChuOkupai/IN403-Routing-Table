#include <stdio.h>
#include <stdlib.h>

// affichage du résultat
void	display(int a, int b, int h)
{
	printf("(%d)(%d)", a, b);
	printf(" ⇒ %d\n", h);
}

// calcul le hash
int	hash(int a, int b, int n)
{
	if (a > b) { int c = a; a = b; b = c; }
	int i = a, s = 0;
	while (i--)
		s += --n;
	return s + b - a - 1;
}

// test le hash, renvoie 1 si le hash est correct pour n noeuds
int	check_hash(int n)
{
	int a, b, h, i;
	for (a = 0, i = 0; a < n; a++)
	{
		for (b = a + 1; b < n; b++)
		{
			h = hash(a, b, n);
			if (h != i)
			{
				display(a, b, h);
				return 0;
			}
			i++;
		}
	}
	return 1;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	int n = atoi(argv[1]);
	if (n < 2)
		return 2;
	printf("hash test (%d nodes)\n", n);
	puts(check_hash(n) ? "Success!" : "Failure");
	return 0;
}