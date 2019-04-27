#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "error.h"
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
	int d[20], i, j, k, n;

	//init sommet degré 2 Tier 2
	memset(d, 0, sizeof(d));
	for(i=0;i<20;i++) d[i] = 2;
	
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
		// Liaison au Tier 2
		// NE MARCHE PAS DANS CERTAINS PETITS CAS
		k = rand()%2 ? k+1 : k;
		k -= d[i-T2_START];
		
		j = 0;
		while (j < k)
		{
			n = rand() % (T2_END-T2_START) + T2_START;
			if (i != n && d[n-T2_START] < 3 && d[i-T2_START] < 3 && !linked(g, i, n))
			{
				LINK(g, i, n, rand() % 11 + 10);
				d[n-T2_START]++;
				d[i-T2_START]++;
				j++;
			}
		}
	}
}

void initTier3(Graph *g)
{
	int i, j, n;
	
	// Liaison au Tier 2
	for (i = T3_START; i < T3_END; i++)
		for (j = 0; j < 2; j++)
		{
			do
				n = rand() % (T2_END-T2_START) + T2_START;
			while (linked(g, i, n));
			LINK(g, i, n, rand() % 36 + 15);
		}
	// Liaison au Tier 3
	for (i = T3_START; i < T3_END; i++)
		if (! g->tab[i]->next->next)
		{
			do
				n = rand() % (T3_END-T3_START) + T3_START;
			while (i == n || g->tab[n]->next->next);
			LINK(g, i, n, rand() % 36 + 15);
		}
}

Graph*	createNetwork()
{
	Graph *g = newGraph(100);
	srand(time(NULL));
	initTier1(g);
	initTier2(g);
	initTier3(g);
	return g;
}

void search_vertex(Graph *g, int v, int *color, int *father)
{
	color[v] = 1;
	Node *n = g->tab[v];
	while(n != NULL)
	{
		if(color[n->id] == 0)
		{
			father[n->id] = v;
			search_vertex(g, n->id, color, father);
		}
		n = n->next;
	}
}

int depthFirstSearch(Graph *g)
{
	if(!g) return 0;
	int i, hasFather = 1;
	int *color, *father;
	
	CHECK(color = calloc(g->size, sizeof(int)));
	CHECK(father = (int*)malloc(g->size*sizeof(int)));
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