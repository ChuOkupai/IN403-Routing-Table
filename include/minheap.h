#ifndef _MINHEAP_H
# define _MINHEAP_H

// Tas min (utilisé avec l'algorithme de Dijkstra)

typedef struct s_MinHeapNode 
{
	int v; // index du sommet
	int d; // distance
}	MinHeapNode;

typedef struct s_MinHeap 
{
	int size;
	int capacity;
	int *position; // la position du noeud dans le tas
	MinHeapNode **tab;
}	MinHeap;

// Crée un noeud
MinHeapNode*	newMinHeapNode(int v, int d);

// Crée un tas min de taille n
MinHeap*	newMinHeap(int capacity);

// Vérifie si le sommet v est dans le tas
int	inMinHeap(MinHeap *h, int v);

// Récupère le noeud minimum du tas
MinHeapNode*	extractMin(MinHeap* h);

// Diminue la priorité du sommet v
void	decreaseKey(MinHeap* h, int v, int d);

// Libère la mémoire d'un tas min
void	destroyMinHeap(MinHeap* h);

#endif