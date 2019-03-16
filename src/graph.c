#include "graph.h"
#include "node.h"

Graph*	newGraph(uint8_t size)
{
	Graph *g = (Graph*)malloc(sizeof(Graph));
	if(g!= NULL)
	{
		g->size = size;
		g->table = (Node**)calloc(size, sizeof(Node*));
		return g;
		
	}
	return NULL;
}

void	linkNode(Graph *g, uint8_t index1, uint8_t weight1, uint8_t index2, uint8_t weight2)
{
	if(!g) return ;
	Node* n1 = g->table[index1];
	Node* n2 = g->table[index2];
	Node* n1prec,n2prec;
	if(!n1) n1 = newNode(index2, weight1);
	else
	{
		while(n1 != NULL && n->index < n1->index)
		{
			n1prec = n1;
			n1 = n1->next;
		}
		n1prec->next = newNode(index2, weight1);
	}
	
	if(!n2) n2 = newNode(index1, weight2);
	else
	{
		while(n1 != NULL && n->index < n2->index)
		{
			n2prec = n2;
			n2 = n2->next;
		}
		n1prec->next = newNode(index1, weight2);
	}
}

void	destroyGraph(Graph *g)
{
	Node* n, nn;
	
	if(!g) return ;
	for(int i=0;i<g->size; i++)
	{
		if(!g->table[i])
		{
			n = g->table[i];
			nn = n->next;
			while(n != NULL)
			{
				free(n)
				n = nn;
				nn = n->next;  
			}
		}
	}
	free(g->table);
	free(g);
}