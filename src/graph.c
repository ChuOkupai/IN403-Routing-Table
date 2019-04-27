#include <stdlib.h>
#include "error.h"
#include "graph.h"

// Crée un noeud
Node*	newNode(int id, int weight)
{
	Node *n;
	CHECK(n = (Node*)malloc(sizeof(Node)));
	n->id = id;
	n->weight = weight;
	n->next = NULL;
	return n;
}

// Crée un graphe
Graph*	newGraph(int n)
{
	Graph *g;
	CHECK(g = (Graph*)malloc(sizeof(Graph)));
	CHECK(g->tab = (Node**)calloc(n, sizeof(Node)));
	g->size = n;
	return g;
}

// Vérifie si le lien du sommet a vers b existe, si oui renvoie son poids
int	linked(Graph *g, int a, int b)
{
	Node *n = g->tab[a];
	int w = 0;
	while (n && ! w)
		if (n->id == b)
			w = g->tab[a]->weight;
		else
			n = n->next;
	return w;
}

// Crée un lien du sommet a vers b (poids > 0 !)
void	link(Graph *g, int a, int b, int weight)
{
	if (! (g && weight))
		return;
	Node *nnew, *ncurr, *nprev;
	
	if(a < 0 || a >= g->size || b < 0 || b >= g->size)
	{
		WARNING(EDOM);
		return ;
	}
	
	nnew = newNode(b, weight);
	
	if(!g->tab[a]) g->tab[a] = nnew;
	else if(g->tab[a] && g->tab[a]->id > b)
	{
		nnew->next = g->tab[a];
		g->tab[a] = nnew;
	}
	
	else
	{
		ncurr = nprev = g->tab[a];
		while(ncurr != NULL && ncurr->id <= b)
		{
			nprev = ncurr;
			ncurr = ncurr->next;
		}
		nnew->next = ncurr;
		nprev->next = nnew;
	}
}

// Affichage du graphe (sur le terminal)
void	drawGraph(Graph *g)
{
	Node *n;
	
	printf("Format: vertex → link 1|weight 1 → ... → link n|weight n\n");
	for (int i = 0; i < g->size; i++)
	{
		n = g->tab[i];
		printf("%2d", i);
		if (! n)
			printf(" → \033[38;2;255;25;25mnull\033[0m"); // pas de voisins
		while (n)
		{
			printf(" → %2d|%2d", n->id, n->weight);
			n = n->next;
		}
		putchar('\n');
	}
}

// Libère la mémoire d'un graphe
void	destroyGraph(Graph *g)
{
	Node *ncurr,*nnext;
	for(int i=0; i<g->size; i++)
	{
		ncurr = g->tab[i];
		if(ncurr != NULL) nnext = ncurr->next;
		while(ncurr != NULL)
		{
			free(ncurr);
			ncurr = nnext;
			if(ncurr)
				nnext = nnext->next;
		}
	}
	free(g->tab);
	free(g);
}