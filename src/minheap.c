#include <stdlib.h>
#include "error.h"
#include "minheap.h"

// Crée un noeud
MinHeapNode*	newMinHeapNode(const int v, const int distance)
{
	MinHeapNode *n;
	CHECK(n = (MinHeapNode*)malloc(sizeof(MinHeapNode)));
	n->v = v;
	n->distance = distance;
	return n;
}

// Crée un tas min de taille n
MinHeap*	newMinHeap(const int capacity)
{
	MinHeap *h;
	
	CHECK(h = (MinHeap*)malloc(sizeof(MinHeap)));
	CHECK(h->position = (uint8_t*)malloc(capacity * sizeof(uint8_t)));
	h->size = 0;
	h->capacity = capacity;
	CHECK(h->tab = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode*)));
	return h;
}

// Vérifie si le sommet v est dans le tas
int	inMinHeap(MinHeap *h, const int v)
{
	return (h->position[v] < h->size) ? 1 : 0;
}

// Echange 2 noeuds
void	swapMinHeapNode(MinHeapNode **a, MinHeapNode **b)
{
	MinHeapNode *c;
	
	c = *a;
	*a = *b;
	*b = c;
}

void	MinHeapify(MinHeap *h, const int i)
{
	int smallest, left, right;
	
	smallest = i;
	left = 2 * i + 1;
	right = 2 * i + 2;
	if (left < h->size && h->tab[left]->distance < h->tab[smallest]->distance)
		smallest = left;
	if (right < h->size && h->tab[right]->distance < h->tab[smallest]->distance)
		smallest = right;
	if (smallest != i)
	{
		h->position[h->tab[smallest]->v] = i;
		h->position[h->tab[i]->v] = smallest;
		swapMinHeapNode(&h->tab[smallest], &h->tab[i]);
		MinHeapify(h, smallest);
	}
}

// Récupère le noeud minimum du tas
MinHeapNode*	extractMin(MinHeap *h)
{
	MinHeapNode *root, *last;
	
	root = h->tab[0];
	last = h->tab[h->size - 1];
	h->tab[0] = last;
	h->position[root->v] = h->size - 1;
	h->position[last->v] = 0;
	h->size--;
	MinHeapify(h, 0);
	return root;
}

// Diminue la priorité du sommet v
void	decreaseKey(MinHeap* h, const int v, const int distance)
{
	int i, m;
	
	i = h->position[v];
	h->tab[i]->distance = distance;
	while (i && h->tab[i]->distance < h->tab[(m = (i - 1)/ 2)]->distance)
	{
		h->position[h->tab[i]->v] = m;
		h->position[h->tab[m]->v] = i;
		swapMinHeapNode(&h->tab[i],  &h->tab[m]);
		i = m;
	}
}

// Libère la mémoire d'un tas min
void	destroyMinHeap(MinHeap *h)
{
	free(h->tab);
	free(h->position);
	free(h);
}