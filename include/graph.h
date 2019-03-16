#ifndef _GRAPH_H
# define _GRAPH_H

#include <stdint.h>

typedef struct s_Graph Graph;
struct s_Graph
{
	uint8_t	n;
	uint8_t	**m;
};

// Crée un graphe de taille n
Graph*	newGraph(uint8_t n);

// Détruit un graphe
void	destroyGraph(Graph *G);

// Ajoute une arête entre 2 sommets du graphe
#define LINK(G, X, Y, WEIGHT) { ((Graph*)G)->m[x][y] = WEIGHT; (Graph*)G)->m[y][x] = WEIGHT; }

// Supprime une arête entre 2 sommets du graphe
#define UNLINK(G, X, Y) { ((Graph*)G)->m[x][y] = 0; (Graph*)G)->m[y][x] = 0; }

#endif