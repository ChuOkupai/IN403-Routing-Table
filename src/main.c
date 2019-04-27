#include "network.h"
#include <stdio.h>

int main()
{
	Graph *g;
	
	do // tant que le réseau n'est pas connexe
		g = createNetwork();
	while (! depthFirstSearch(g));
	drawGraph(g);
	destroyGraph(g);
	return 0;
}