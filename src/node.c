#include <stdlib.h>
#include "node.h"

Node*	newNode(uint8_t index, uint8_t weight)
{
	Node *n = (Node*)malloc(sizeof(Node));
	
	if (! n)
		return n;
	n->index = index;
	n->weight = weight;
	return n;
}

void	destroyNode(Node *n)
{
	free(n);
}