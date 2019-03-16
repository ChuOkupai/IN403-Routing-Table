#include <errno.h>
#include <stdlib.h>
#include "graph.h"
#include "node.h"

#define _return_malloc_error() { destroyGraph(g); errno = ENOMEM; return NULL; }

Graph*	newGraph(uint8_t size)
{
	Graph *g = (Graph*)malloc(sizeof(Graph));
	
	if (! g)
		return g;
	g->size = size;
	g->table = (Node**)calloc(size, sizeof(Node*));
	if (! g->table)
		_return_malloc_error();
	for (uint8_t i = 0; i < size; i++)
	{
		g->table[i] = newNode(i, 0);
		if (! g->table[i])
			_return_malloc_error();
	}
	return g;
}

/*void	linkNode(Graph *g, uint8_t index1, uint8_t weight1, uint8_t index2, uint8_t weight2)
{
	if(!g) return ;
	Node* n1 = g->table[index1];
	Node* n2 = g->table[index2];
	Node* n1prec,n2prec;
	if(!n1) n1 = newNode(index2, weight1);
	else
	{
		while(n1 != NULL)
		{
			n1prec = n1;
			n1 = n1->next;
		}
		n1prec->next = newNode(index2, weight1);
	}
	
	if(!n2) n2 = newNode(index1, weight2);
	else
	{
		while(n1 != NULL)
		{
			n2prec = n2;
			n2 = n2->next;
		}
		n2prec->next = newNode(index1, weight2);
	}
}*/

void	destroyGraph(Graph *g)
{
	if (! g)
		return;
	else if (! g->table)
	{
		free(g);
		return;
	}
	Node *next;
	
	for (uint8_t i = 0; i < g->size; i++)
	{
		if (! g->table[i])
			continue;
		while (g->table[i])
		{
			next = g->table[i]->next;
			free(g->table[i]);
			g->table[i] = next;
		}
	}
	free(g->table);
	free(g);
}