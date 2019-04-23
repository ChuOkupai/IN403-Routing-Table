#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "network.h"

#define START_TIER1 0
#define END_TIER1 8
#define START_TIER2 END_TIER1
#define END_TIER2 28
#define START_TIER3 END_TIER2
#define END_TIER3 100

Graph	createNetwork()
{
	//int nbTier[72];
	int i, j;
	//int n1,n2;
	Graph g = graphInit(100);
	srand(time(NULL));
	
	//Tier 1
	for (i = 0; i < END_TIER1 - 1; i++)
		for (j = i + 1; j < END_TIER1; j++)
			if (rand() % 4)
				LINK(g,i,j,rand() % 6 + 5);
	
	/* C'EST BUGGEEEEEEEEEEE !
	//TIER2
	memset(nbTier, 0, sizeof(nbTier));
	
	for(i=START_TIER2;i<END_TIER2;i++)
	{
		//Liaison au TIER1
		n2 = n1 = randi(START_TIER1, END_TIER1 - 1);
		LINK(g,i,n1,randi(10,20));
		if(randi(1,2) == 2)
		{
			while(n1 == n2)
				n2 = randi(START_TIER1, END_TIER1 - 1);
			LINK(g,i,n2,randi(10,20));
		}
		
		
		//Liaison au TIER2 FAUX
		j = randi(2,3);
		while(nbTier[i - START_TIER2] < j)
		{
			n1 = randi(START_TIER2, END_TIER2 - 1);
			if(!alreadyLinked(g,i,n1) && nbTier[n1 - START_TIER2] < 3 && n1 != i)
			{
				LINK(g,i,n1,randi(10,20));
				nbTier[i - START_TIER2]++;
				nbTier[n1 - START_TIER2]++;
			}
		}
	}
	//TIER3
	memset(nbTier, 0, sizeof(nbTier));
	
	for(i=START_TIER3;i<END_TIER3; i++)
	{
		//Liasion au TIER2
		n2 = n1 = randi(START_TIER2, END_TIER2 - 1);
		LINK(g,i,n1,randi(15,50));
		while(n1 == n2)
			n2 = randi(START_TIER2, END_TIER2 - 1);
		LINK(g,i,n2,randi(15,50));
		
		//Liaison au TIER3 FAUX
		n1 = randi(START_TIER3,END_TIER3-1);
		while(nbTier[i - START_TIER3] < 1 )
		{
			if(!alreadyLinked(g,i,n1) && nbTier[n1 - START_TIER3] < 1 && n1 != i)
			{
				nbTier[i - START_TIER3]++;
				nbTier[n1 - START_TIER3]++;
			}
		}
		LINK(g,i,randi(START_TIER3,END_TIER3-1),randi(15,50));
	}
	*/
	return g;
}

void search_vertex(Graph g, int s, int *color, int *father)
{
	color[s] = 1;
	Node n = g->tab[s];
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

int depthFirstSearch(Graph g)
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
