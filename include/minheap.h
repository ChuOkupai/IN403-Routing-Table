#ifndef _MINHEAP_H
# define _MINHEAP_H

// Implémentation d'un tas min
/// Utilisé avec l'algorithme de Dijkstra

#include <stdint.h>

typedef struct s_MinHeapNode 
{
	uint8_t v; // index du sommet
	uint8_t distance; // distance depuis la source
}	MinHeapNode;

typedef struct s_MinHeap 
{
	uint8_t size;
	uint8_t capacity;
	uint8_t *position; // la position du noeud dans le tas
	MinHeapNode **tab;
}	MinHeap;

// Crée un noeud
MinHeapNode*	newMinHeapNode(const int v, const int distance);

// Crée un tas min de taille n
MinHeap*	newMinHeap(const int capacity);

// Vérifie si le sommet v est dans le tas
int	inMinHeap(MinHeap *h, const int v);

// Récupère le noeud minimum du tas
MinHeapNode*	extractMin(MinHeap* h);

// Diminue la priorité du sommet v
void	decreaseKey(MinHeap* h, const int v, const int distance);

// Libère la mémoire d'un tas min
void	destroyMinHeap(MinHeap* h);

#endif