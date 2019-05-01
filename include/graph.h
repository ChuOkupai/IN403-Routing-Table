#ifndef _GRAPH_H
# define _GRAPH_H

#include <stdint.h>

typedef struct s_Node
{
	uint8_t id;
	uint8_t weight;
	struct s_Node *next;
}	Node;

typedef struct s_Graph
{
	uint8_t size;
	Node **tab;
}	Graph;

// Crée un graphe de taille n
Graph*	newGraph(const int n);

// Vérifie si l'arête du sommet a vers b existe
/// Renvoie son poids si oui, 0 sinon
int8_t	linked(Graph *g, const int a, const int b);

// Crée une arête du sommet a vers b
/// Le poids doit être supérieur à 0 !
void	link(Graph *g, const int a, const int b, const int weight);

// Supprime une arête du sommet a vers b
void	rmlink(Graph *g, const int a, const int b);

// Applique le parcours en profondeur pour vérifier la connexité du graphe
/// Renvoie 1 si le graphe est connexe, 0 sinon
int8_t depthFirstSearch(const Graph *g);

// Calcul des distances à partir du sommet a via l'algorithme de Dijkstra
/// Les résultats sont stockés dans distance et parent qui doivent être initialisés de taille g->size !
void	dijkstra(const Graph* g, uint8_t *distance, int8_t *parent, const int a);

// Affiche le résultat de l'agorithme de Dijkstra
void	displayShortestPaths(const uint8_t *distance, const int8_t *parent, const int a, const int n);

// Affichage du graphe sur le terminal
void	displayGraph(const Graph *g);

// Libère la mémoire d'un graphe
void	destroyGraph(Graph *g);

#endif