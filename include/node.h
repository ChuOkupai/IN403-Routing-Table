#ifndef _NODE_H
# define _NODE_H

#include <stdint.h>

typedef struct s_Node Node;
struct s_Node
{
	uint8_t	index;
	uint8_t	weight;
	Node	*next;
};

Node*	newNode(uint8_t index, uint8_t weight);

void	destroyNode(Node *n);

#endif