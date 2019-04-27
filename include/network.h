#ifndef _NETWORK_H
# define _NETWORK_H

#include "graph.h"

#define T1_START 0
#define T1_END 8
#define T2_START T1_END
#define T2_END 28
#define T3_START T2_END
#define T3_END 100
#define SIZE T3_END

typedef struct s_RootingTable
{
	int *distance; // tableau des distances
	int *parent; // tableau des pères
}	RootingTable;

// Crée le réseau
Graph*	createNetwork();

// Crée la table de routage en calculant les chemins
RootingTable*	createRootingTable(Graph *g);

// Libère la mémoire de la table de routage
void	destroyRootingTable(RootingTable *r);

#endif