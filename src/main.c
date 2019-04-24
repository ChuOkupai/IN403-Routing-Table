#include "network.h"
#include <stdio.h>

int main()
{
	Graph *g = graphInit(2);
	LINK(g, 0, 1, 10);
	printf("recherche ? %d\n", depthFirstSearch(g));
	graphDestroy(g);
	return 0;
}
