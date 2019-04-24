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

Graph	createNetwork()
{
	//int nbTier[72];
	int i, j;
	//int n1,n2;
	Graph *g = graphInit(100);
	srand(time(NULL));
	
	//Tier 1
	for (i = 0; i < T1_END - 1; i++)
		for (j = i + 1; j < T1_END; j++)
			if (rand() % 4)
				LINK(g,i,j,rand() % 6 + 5);
	
	/* C'EST BUGGEEEEEEEEEEE !
	//TIER2
	memset(nbTier, 0, sizeof(nbTier));
	
	for(i=T2_START;i<T2_END;i++)
	{
		//Liaison au TIER1
		n2 = n1 = randi(T1_START, T1_END - 1);
		LINK(g,i,n1,randi(10,20));
		if(randi(1,2) == 2)
		{
			while(n1 == n2)
				n2 = randi(T1_START, T1_END - 1);
			LINK(g,i,n2,randi(10,20));
		}
		
		
		//Liaison au TIER2 FAUX
		j = randi(2,3);
		while(nbTier[i - T2_START] < j)
		{
			n1 = randi(T2_START, T2_END - 1);
			if(!alreadyLinked(g,i,n1) && nbTier[n1 - T2_START] < 3 && n1 != i)
			{
				LINK(g,i,n1,randi(10,20));
				nbTier[i - T2_START]++;
				nbTier[n1 - T2_START]++;
			}
		}
	}
	//TIER3
	memset(nbTier, 0, sizeof(nbTier));
	
	for(i=T3_START;i<T3_END; i++)
	{
		//Liasion au TIER2
		n2 = n1 = randi(T2_START, T2_END - 1);
		LINK(g,i,n1,randi(15,50));
		while(n1 == n2)
			n2 = randi(T2_START, T2_END - 1);
		LINK(g,i,n2,randi(15,50));
		
		//Liaison au TIER3 FAUX
		n1 = randi(T3_START,T3_END-1);
		while(nbTier[i - T3_START] < 1 )
		{
			if(!alreadyLinked(g,i,n1) && nbTier[n1 - T3_START] < 1 && n1 != i)
			{
				nbTier[i - T3_START]++;
				nbTier[n1 - T3_START]++;
			}
		}
		LINK(g,i,randi(T3_START,T3_END-1),randi(15,50));
	}
	*/
	return g;
}

void search_vertex(Graph *g, int s, int *color, int *father)
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
