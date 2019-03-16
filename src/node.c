#include <stdint.h>
#include <stdlib.h>
#include "node.h"

struct s_Node
{
	uint8_t	index;
	Node	*next;
};