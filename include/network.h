#ifndef _NETWORK_H
# define _NETWORK_H

#include "graph.h"

#define T1_START 0
#define T1_END 8
#define T2_START T1_END
#define T2_END 28
#define T3_START T2_END
#define T3_END 100

Graph*	createNetwork();

int	depthFirstSearch(Graph *g);

#endif