#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "graph.h"

Node newNode(int id, int weight)
{
	Node n = (Node)malloc(sizeof(struct node));
	if(!n) ERROR_EXIT();
	n->id = id;
	n->weight = weight;
	n->next = NULL;
	return n;
}

int alreadyLinked(Graph g, int id1, int id2)
{
	int found = 0;
	Node ncurr = g->tab[id1];
	while(ncurr != NULL && !found)
	{
		if(ncurr->id == id2){found = 1;}
		else ncurr = ncurr->next;
	}
	return found;
}

void linkNode(Graph g, int id1, int id2, int weight)
{
	Node nnew, ncurr, nprev;
	
	if(!g) ERROR_EXIT();
	if(id1 < 0 || id1 >= g->nbNode || id2 < 0 || id2 >= g->nbNode)
	{
		WARNING(EDOM);
		return ;
	}
	
	nnew = newNode(id2, weight);
	
	if(!g->tab[id1]) g->tab[id1] = nnew;
	else if(g->tab[id1] && g->tab[id1]->id > id2)
	{
		nnew->next = g->tab[id1];
		g->tab[id1] = nnew;
	}
	
	else
	{
		ncurr = nprev = g->tab[id1];
		while(ncurr != NULL && ncurr->id <= id2)
		{
			nprev = ncurr;
			ncurr = ncurr->next;
		}
		nnew->next = ncurr;
		nprev->next = nnew;
	}
}

Graph graphInit(int n)
{
	if(n <= 0){WARNING(EDOM);return NULL;}
	Graph g = (Graph)malloc(sizeof(struct graph));
	if(!g) return NULL;
	g->nbNode = n;
	g->tab = (Node*)calloc(n, sizeof(struct node));
	if(!(g->tab)){free(g); return NULL;}
	return g;
}

void graphDestroy(Graph g)
{
	
	Node ncurr,nnext;
	for(int i=0; i<g->nbNode; i++)
	{
		ncurr = g->tab[i];
		if(ncurr != NULL) nnext = ncurr->next;
		while(ncurr != NULL)
		{
			free(ncurr);
			ncurr = nnext;
			if(ncurr)
				nnext = nnext->next;
		}
	}
	free(g->tab);
	free(g);
}

void graphDraw(Graph g)
{
	int i;
	Node ncurr;
	printf("Graphe avec %d sommets \n",g->nbNode);
	for(i = 0; i<g->nbNode; i++){
		printf("Voisins de %d: ",i);
		ncurr = g->tab[i];
		while(ncurr != NULL)
		{
			printf("%d(%d)",ncurr->id, ncurr->weight);
			ncurr = ncurr->next;
		}
		printf("\n");
	}
}