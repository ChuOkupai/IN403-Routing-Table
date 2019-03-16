#include <stdlib.h>
#include "error.h"
#include "graph.h"

Graph*	newGraph(uint8_t n)
{
	if (! n)
		return NULL;
	Graph *G = (Graph*)malloc(sizeof(Graph));
	
	if (! G)
		ERROR_EXIT();
	G->n = n;
	G->m =(uint8_t**)malloc(n * sizeof(uint8_t*));
	if (! G->m)
		ERROR_EXIT();
	for (uint16_t i = 0; i < n; i++)
	{
		G->m[i] = (uint8_t*)calloc(G->n, sizeof(uint8_t));
		if (! G->m[i])
			ERROR_EXIT();
	}
	return G;
}

void	destroyGraph(Graph *G)
{
	if (! G)
		return;
	for (uint16_t i = 0; i < G->n; i++)
		free(G->m[i]);
	free(G->m);
	free(G);
}