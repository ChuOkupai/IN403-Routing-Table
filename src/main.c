#include "network.h"

// Gestion du debug
/// activé si valeur non nulle
#define DEBUG 1

int main()
{
	Graph *g;
	RootingTable *r;
	
	g = createNetwork();
	r = createRootingTable(g);
	#if DEBUG
		displayGraph(g);
		// Affichage des chemins possibles pour le premier noeud
		displayShortestPaths(r[0].distance, r[0].parent, 0, g->size);
	#endif
	destroyGraph(g);
	destroyRootingTable(r);
	return 0;
}