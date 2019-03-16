#include <stdint.h>
#include <stdlib.h>
#include "node.h"

struct s_Node
{
	uint8_t	index;
	uint8_t	weight;
	Node	*next;
};

#define TIER1_MIN 0
#define TIER1_MAX 7
#define TIER2_MIN (TIER1_MAX + 1)
#define TIER2_MAX 27
#define TIER3_MIN (TIER2_MAX + 1)
#define TIER3_MAX 99