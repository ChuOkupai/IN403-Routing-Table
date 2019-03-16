#ifndef _GRAPH_H
# define _GRAPH_H

typedef struct s_Graph Graph;
struct s_Graph
{
	uint8_t	size;
	Node		**table;
};

Graph*	newGraph(uint8_t size);

void	insertNode(Graph *g, uint8_t index);

void	destroyGraph(Graph *g);

#endif