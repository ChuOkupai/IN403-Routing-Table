#include <stdio.h>
#include <stdlib.h>
#include "network.h"


int main()
{
	Graph g = createNetwork(28);
	graphDraw(g);
	graphDestroy(g);
	return 0;
}