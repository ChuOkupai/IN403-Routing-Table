#include "network.h"

int main()
{
	Graph g = createNetwork();
	graphDraw(g);
	graphDestroy(g);
	return 0;
}