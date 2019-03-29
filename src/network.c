#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "network.h"

#define START_TIER1 0
#define END_TIER1 8
#define START_TIER2 END_TIER1
#define END_TIER2 28
#define START_TIER3 END_TIER2
#define END_TIER3 100

int randi(int min, int max)
{
	// on considere min et max positifs
	return rand()%(max - min + 1) + min;
}

Graph	createNetwork(int n)
{
	int nbTier[72];
	int i, j;
	int n1,n2;
	Graph g = graphInit(n);
	srand(time(NULL));
	
	//Tier 1
	for(i=START_TIER1;i<END_TIER1;i++)
	{
		//Liaison au TIER1 
		for(j=START_TIER1;j<END_TIER1;j++)
		{
			if(!alreadyLinked(g, i, j) && randi(1,4) > 1 && i!=j) //si dans g i n'est pas lié à j et ...
				LINK(g,i,j,randi(5,10));
		}
	}
	
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
	/*
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
	int i;
	int hasFather = 1;
	int *color = calloc(g->nbNode, sizeof(int)); // 0 est blanc, 1 gris et 2 noir
	int *father = calloc(g->nbNode, sizeof(int));
	
	for(i=0; i<g->nbNode; i++)
	{
		if(color[i] == 0)
			search_vertex(g,i,color,father);
	}
	
	i=0;
	while(i<g->nbNode && hasFather)
	{
		if(father[i] == 0) hasFather = 0;
		i++;
	}
	
	free(color);
	free(father);
	return hasFather;
}

