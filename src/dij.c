#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "minheap.h"

// QUELQUES TESTS

// Affiche le chemin
void	renderPath(int parent[], int v)
{
	if (parent[v] == -1)
		return;
	renderPath(parent, parent[v]);
	if (v < 26) printf("%c ", v + 'A');
		else printf("(%d) ", v);
}

// Affiche le résultat
void	display(int dist[], int parent[], int a, int n)
{
	// Affichage des distances et chemins
	printf("Distances from ");
	if (a < 26) printf("%c", a + 'A');
		else printf("(%d)", a);
	printf(":\n");
	for (int v = 0; v < n; v++)
	{
		if (v < 26) printf("%c", v + 'A');
		else printf("(%d)", v);
		printf(" → ");
		if (dist[v] != INT_MAX)
		{
			printf("%d", dist[v]);
			if (v != a)
			{
				printf(" path: ");
				renderPath(parent, v);
			}
		}
		else
			printf("∞");
		putchar('\n');
	}
	// Affichage du tableau des pères
	printf("Table: [");
	for (int i = 0; i < n; i++)
	{
		if (parent[i] != INT_MAX)
			printf("%d", parent[i]);
		else
			printf("∞");
		if (i + 1 < n)
			printf(", ");
	}
	printf("]\n");
}

// Calcul des distances à partir du sommet a via l'algorithme de Dijkstra
void	dijkstra(Graph* g, int a)
{
	MinHeap *h;
	MinHeapNode *e;
	Node *n;
	int dist[g->size], parent[g->size], u, v;
	
	// Initialisation
	h = newMinHeap(g->size);
	h->size = g->size;
	for (v = 0; v < g->size; v++)
	{
		dist[v] = INT_MAX; // valeur infini
		h->tab[v] = newMinHeapNode(v, dist[v]);
		h->position[v] = v;
	}
	dist[a] = 0; // On définit la valeur du sommet de départ à 0
	parent[a] = -1;
	decreaseKey(h, a, dist[a]);
	
	// Tant qu'il y a des noeuds dont la plus courte distance n'a pas été trouvée
	while (h->size)
	{
		e = extractMin(h);
		u = e->v;
		free(e);
		n = g->tab[u];
		// On met à jour la distance de tous les voisins
		while (n)
		{
			v = n->id;
			// Si la distance vers v n'est pas terminée et si la distance actuelle est plus courte que la précédente
			if (inMinHeap(h, v) && dist[u] != INT_MAX && n->weight + dist[u] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + n->weight;
				decreaseKey(h, v, dist[v]);
			}
			n = n->next;
		}
	}
	destroyMinHeap(h);
	
	// Correction des chemins impossibles
	for (v = 0; v < g->size; v++)
		if (dist[v] == INT_MAX)
			parent[v] = INT_MAX; // reset valeur infini
	// Affichage des distances (DEBUG)
	display(dist, parent, a, g->size);
}

// Juste pour simplifier la création des arêtes
enum e_vertex
{
	A,
	B,
	C,
	D,
	E,
	F,
	G
};

void	test1(Graph *g)
{
	LINK(g, A, B, 1);
	LINK(g, A, C, 1);
	LINK(g, B, C, 3);
	LINK(g, B, F, 10);
	LINK(g, C, D, 2);
	LINK(g, C, E, 4);
	LINK(g, D, F, 4);
	LINK(g, E, F, 3);
}

void	test2(Graph *g)
{
	LINK(g, A, B, 2);
	LINK(g, A, E, 3);
	LINK(g, B, C, 5);
	LINK(g, B, E, 4);
	LINK(g, B, F, 2);
	LINK(g, C, D, 2);
	LINK(g, C, F, 4);
	LINK(g, D, E, 2);
	LINK(g, D, F, 5);
	LINK(g, E, F, 2);
}

void	test3(Graph *g)
{
	LINK(g, A, B, 1);
	LINK(g, B, C, 2);
	LINK(g, C, D, 3);
	LINK(g, D, E, 4);
	LINK(g, E, F, 5);
	LINK(g, F, G, 6);
	LINK(g, G, A, 7);
}

int main()
{
	int n = 7;
	Graph *g = newGraph(n);
	
	test3(g);
	for (int i = 0; i < n; i++)
	{
		dijkstra(g, i);
		if (i + 1 < n)
			putchar('\n');
	}
	destroyGraph(g);
	return 0;
}