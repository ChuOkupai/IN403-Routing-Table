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
	CHECK(g = (Graph*)malloc(sizeof(struct graph)));
	CHECK(g->tab = (Node**)calloc(n, sizeof(struct node)));
	g->size = n;
	return g;
}

// Vérifie si le lien du sommet a vers b existe
int	linked(Graph *g, int a, int b)
{
	Node *n = g->tab[a];
	int found = 0;
	while (n && ! found)
		if (n->id == b)
			found = 1;
		else
			n = n->next;
	return found;
}

// Crée un lien du sommet a vers b
void	link(Graph *g, int a, int b, int weight)
{
	if (! g)
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
	
	for (int i = 0; i < g->size; i++)
	{
		n = g->tab[i];
		if (! n)
			continue;
		printf("%d:", i);
		while (n)
		{
			printf("%2d(%2d)", n->id, n->weight);
			if ((n = n->next))
				putchar(',');
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