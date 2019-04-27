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

// Vérifie si l'arête du sommet a vers b existe
/// Renvoie son poids si oui, 0 sinon
int	linked(Graph *g, int a, int b);

// Crée une arête du sommet a vers b
/// Le poids doit être supérieur à 0 !
void	link(Graph *g, int a, int b, int weight);

// Affichage du graphe sur le terminal
void	drawGraph(Graph *g);

// Libère la mémoire d'un graphe
void	destroyGraph(Graph *g);

// Création d'une arête entre 2 sommets
/// Le poids doit être supérieur à 0 !
#define LINK(g, a, b, w) ({link(g, a, b, w); link(g, b, a, w);})

#endif