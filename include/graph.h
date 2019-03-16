#ifndef _GRAPH_H
# define _GRAPH_H

#include <stdint.h>

typedef struct s_Graph Graph;
struct s_Graph
{
	uint8_t	size;
	Node	**table;
};

Graph*	newGraph(uint8_t size);

void	linkNode(Graph *g, uint8_t index1, uint8_t weight1, uint8_t index2, uint8_t weight2);

void	destroyGraph(Graph *g);

#endif