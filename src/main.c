#include "network.h"

int	main()
{
	Graph *G = createNetwork();
	destroyGraph(G);
	return 0;
}