#include <stdio.h>
#include <stdlib.h>

// affichage du résultat
void	display(int a, int b, int h)
{
	printf("(%d)(%d)", a, b);
	printf(" ⇒ %d\n", h);
}

// calcul le hash (pour la table de routage)
/** IMPORTANT: a != b **/
int	hash(int a, int b)
{
	if (a > b) { int c = a; a = b; b = c; }
	return (b - 1) * b / 2 + a;
}

// test le hash pour n noeuds, renvoie 1 si correct
int	check_hash(int n)
{
	int a, b, h, i, r = 1;
	for (b = 1, i = 0; b < n && r; b++)
	{
		for (a = 0; a < b; a++)
		{
			h = hash(a, b);
			if (i != h)
			{
				display(a, b, h);
				r = 0;
				break;
			}
			i++;
		}
	}
	return r;
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