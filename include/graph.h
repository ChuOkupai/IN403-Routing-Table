#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdint.h>

typedef struct node
{
	 int id;
	 int weight;
	 struct node* next;
}	Node;

typedef struct graph
{
	int nbNode;
	Node** tab;
}	Graph;

Node *newNode(int id, int weight);
int alreadyLinked(Graph *g, int id1, int id2);
void linkNode(Graph *g, int id1, int id2, int weight);
Graph *graphInit(int n);
void graphDestroy(Graph *g);
void graphDraw(Graph *g);

#define LINK(g,id1,id2,w) {linkNode(g, id1, id2, w); linkNode(g, id2, id1, w);}

#endif
