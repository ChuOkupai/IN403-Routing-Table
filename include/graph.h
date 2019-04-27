#ifndef _GRAPH_H
# define _GRAPH_H

typedef struct s_Node
{
	int id;
	int weight;
	struct s_Node *next;
}	Node;

typedef struct s_Graph
{
	int size;
	Node **tab;
}	Graph;

// Crée un graphe de taille n
Graph*	newGraph(int n);

// Vérifie si le lien du sommet a vers b existe, si oui renvoie son poids
int	linked(Graph *g, int a, int b);

// Crée un lien du sommet a vers b (poids > 0 !)
void	link(Graph *g, int a, int b, int weight);

// Affichage du graphe (sur le terminal)
void	drawGraph(Graph *g);

// Libère la mémoire d'un graphe
void	destroyGraph(Graph *g);

// Création d'un lien entre 2 sommets
#define LINK(g, a, b, w) ({link(g, a, b, w); link(g, b, a, w);})

#endif