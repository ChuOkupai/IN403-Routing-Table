#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "network.h"

void initTier1(Graph *g)
{
	int i,j;
	for (i = 0; i < T1_END; i++)
		for (j = i + 1; j < T1_END; j++)
			if (rand() % 4)
				LINK(g, i, j, rand() % 6 + 5);
}


void initTier2(Graph *g)
{
	int d[20], i, j, k, n;//l, m, n;
	//m = 0;
	memset(d, 0, sizeof(d));
	for (i = T2_START; i < T2_END; i++)
	{
		// Liaison au Tier 1
		j = 0;
		k = rand() % 2 + 1;
		while (j < k)
		{
			n = rand() % T1_END;
			if (linked(g, i, n))
				continue;
			LINK(g, i, n, rand() % 11 + 10);
			j++;
		}
		
		/*
		// Liaison au Tier 2
		j = 0;
		k = rand() % 2 + 2 - d[i - T2_START];
		while (j < k)
		{

			j++;
		}
		* */
	}
}

void initTier3(Graph *g)
{
	int d[72], i, j, n;
	memset(d, 0, sizeof(d));
	
	for (i = T3_START; i < T3_END; i++)
	{
		// Liaison au Tier 2
		j = 0;
		while (j < 2)
		{
			n = rand() % (T2_END-T2_START) + T2_START;
			if (linked(g, i, n))
				continue;
			LINK(g, i, n, rand() % 36 + 15);
			j++;
		}
		
		// Liaison au Tier 3
		if(d[i-T3_START] == 0)
		{
			n = rand() % (T3_END-T3_START) + T3_START;
			while(i == n || d[n-T3_START])
			{
				n = rand() % (T3_END-T3_START) + T3_START;
			}
			LINK(g,i,n,rand() % 36 + 15);
			d[i-T3_START]++;
			d[n-T3_START]++;
		}
	}
}

Graph*	createNetwork()
{
	Graph *g = newGraph(100);
	srand(time(NULL));
	
	initTier2(g);
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
	int *color = calloc(g->size, sizeof(int));
	int *father = (int*)malloc(g->size*sizeof(int));
	for(i=0;i<g->size;i++)
		father[i] = -1;
	
	for(i=0; i<g->size; i++)
		if(color[i] == 0)
			search_vertex(g,i,color,father);

	for(i=1;i<g->size && hasFather;i++)
		if(father[i] == -1) hasFather = 0;

	free(color);
	free(father);
	return hasFather;
}

