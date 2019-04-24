#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "network.h"

#define T1_START 0
#define T1_END 8
#define T2_START T1_END
#define T2_END 28
#define T3_START T2_END
#define T3_END 100

Graph*	createNetwork()
{
	int d[20], i, j, k, l, m, n;
	Graph *g = graphInit(100);
	srand(time(NULL));
	
	// Tier 1
	for (i = 0; i < T1_END; i++)
		for (j = i + 1; j < T1_END; j++)
			if (rand() % 4)
				LINK(g, i, j, rand() % 6 + 5);
	// Tier 2
	m = 0;
	memset(d, 0, sizeof(d));
	for (i = T2_START; i < T2_END; i++)
	{
		// Liaison au Tier 1
		j = 0;
		k = rand() % 2 + 1;
		while (j < k)
		{
			n = rand() % T1_END;
			if (alreadyLinked(g, i, n))
				continue;
			LINK(g, i, n, rand() % 11 + 10);
			j++;
		}
		
		// Liaison au Tier 2
		j = 0;
		k = rand() % 2 + 2 - d[i - T2_START];
		while (j < k)
		{

			j++;
		}
	}
	// Tier 3
	return g;
}

void search_vertex(Graph *g, int s, int *color, int *father)
{
	color[s] = 1;
	Node *n = g->tab[s];
	while(n != NULL)
	{
		if(color[n->id] == 0)
		{
			father[n->id] = s;
			search_vertex(g, n->id, color, father);
		}
		n = n->next;
	}
}

int depthFirstSearch(Graph *g)
{
	if(!g) return 0;
	int i, hasFather = 1;
	int *color = calloc(g->nbNode, sizeof(int));
	int *father = (int*)malloc(g->nbNode*sizeof(int));
	for(i=0;i<g->nbNode;i++)
		father[i] = -1;
	
	for(i=0; i<g->nbNode; i++)
		if(color[i] == 0)
			search_vertex(g,i,color,father);

	for(i=1;i<g->nbNode && hasFather;i++)
		if(father[i] == -1) hasFather = 0;

	free(color);
	free(father);
	return hasFather;
}
