#include "network.h"
#include <stdio.h>

int main()
{
	Graph *g = createNetwork();
	drawGraph(g);
	destroyGraph(g);
	return 0;
}