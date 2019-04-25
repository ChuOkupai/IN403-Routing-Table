#ifndef _GRAPH_H
# define _GRAPH_H

typedef struct node
{
	int id;
	int weight;
	struct node *next;
}	Node;

typedef struct graph
{
	int size;
	Node **tab;
}	Graph;

// Crée un graphe de taille n
Graph*	newGraph(int n);

// Vérifie si le lien du sommet a vers b existe
int	linked(Graph *g, int a, int b);

// Crée un lien du sommet a vers b
void	link(Graph *g, int a, int b, int weight);

// Affichage du graphe (sur le terminal)
void	drawGraph(Graph *g);

// Libère la mémoire d'un graphe
void	destroyGraph(Graph *g);

// Création d'un lien entre 2 sommets
#define LINK(g, a, b, w) ({link(g, a, b, w); link(g, b, a, w);})

#endif