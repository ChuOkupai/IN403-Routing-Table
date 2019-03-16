#include <stdlib.h>
#include <time.h>
#include "network.h"

// Vérifie si le réseau est connexe
/** Renvoie 1 si vrai, 0 sinon **/
char	checkNetwork(Graph *G)
{
	if (! G)
		return 0;
	
	return 1;
}

Graph*	createNetwork()
{
	Graph *G = NULL;
	
	srand(time(NULL));
	while (! checkNetwork(G)) // On recommence tant que le graphe n'est pas connexe
	{
		destroyGraph(G);
		G = newGraph(100);
		
		// traitement des sommets
	}
	return G;
}

void	renderNetwork(Graph *G)
{
	(void)G;
}