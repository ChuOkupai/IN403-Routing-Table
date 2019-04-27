#include <limits.h>
#include <stdlib.h>
#include "error.h"
#include "graph.h"
#include "minheap.h"

// Crée un noeud
Node*	newNode(int id, int weight)
{
	Node *n;
	CHECK(n = (Node*)malloc(sizeof(Node)));
	n->id = id;
	n->weight = weight;
	n->next = NULL;
	return n;
}

// Crée un graphe
Graph*	newGraph(int n)
{
	Graph *g;
	CHECK(g = (Graph*)malloc(sizeof(Graph)));
	CHECK(g->tab = (Node**)calloc(n, sizeof(Node)));
	g->size = n;
	return g;
}

// Vérifie si l'arête du sommet a vers b existe
/// Renvoie son poids si oui, 0 sinon
int	linked(Graph *g, int a, int b)
{
	if (! g) return 0;
	Node *n = g->tab[a];
	int w = 0;
	while (n && ! w)
		if (n->id == b)
			w = g->tab[a]->weight;
		else
			n = n->next;
	return w;
}

// Crée une arête du sommet a vers b
/// Le poids doit être supérieur à 0 !
void	link(Graph *g, int a, int b, int weight)
{
	if (! g || weight < 1 ||  a < 0 || a >= g->size || b < 0 || b >= g->size)
		return;
	Node *nnew, *ncurr, *nprev;
	
	nnew = newNode(b, weight);
	
	if(!g->tab[a]) g->tab[a] = nnew;
	else if(g->tab[a] && g->tab[a]->id > b)
	{
		nnew->next = g->tab[a];
		g->tab[a] = nnew;
	}
	else
	{
		ncurr = nprev = g->tab[a];
		while(ncurr != NULL && ncurr->id <= b)
		{
			nprev = ncurr;
			ncurr = ncurr->next;
		}
		nnew->next = ncurr;
		nprev->next = nnew;
	}
}

// Recherche un sommet
/// Fonction utilitaire pour le parcours en profondeur
void searchVertex(Graph *g, int v, int *color, int *father)
{
	color[v] = 1;
	Node *n = g->tab[v];
	while(n)
	{
		if(color[n->id] == 0)
		{
			father[n->id] = v;
			searchVertex(g, n->id, color, father);
		}
		n = n->next;
	}
}

// Applique le parcours en profondeur pour vérifier la connexité du graphe
/// Renvoie 1 si le graphe est connexe, 0 sinon
int depthFirstSearch(Graph *g)
{
	if(!g) return 0;
	int i, hasFather = 1;
	int *color, *father;
	
	CHECK(color = calloc(g->size, sizeof(int)));
	CHECK(father = (int*)malloc(g->size*sizeof(int)));
	for(i=0;i<g->size;i++)
		father[i] = -1;
	
	for(i=0; i<g->size; i++)
		if(color[i] == 0)
			searchVertex(g,i,color,father);
	
	for(i=1;i<g->size && hasFather;i++)
		if(father[i] == -1) hasFather = 0;
	
	free(color);
	free(father);
	return hasFather;
}

// Calcul des distances à partir du sommet a via l'algorithme de Dijkstra
/// Les résultats sont stockés dans distance et parent qui doivent être initialisés de taille g->size !
void	dijkstra(Graph* g, int *distance, int *parent, int a)
{
	if (! (distance && parent)) return;
	MinHeap *h;
	MinHeapNode *e;
	Node *n;
	int u, v;
	
	// Initialisation
	h = newMinHeap(g->size);
	h->size = g->size;
	for (v = 0; v < g->size; v++)
	{
		distance[v] = INT_MAX; // valeur infini
		h->tab[v] = newMinHeapNode(v, distance[v]);
		h->position[v] = v;
	}
	distance[a] = 0; // On définit la valeur du sommet de départ à 0
	parent[a] = -1;
	decreaseKey(h, a, distance[a]);
	
	// Tant qu'il y a des noeuds dont la plus courte distance n'a pas été trouvée
	while (h->size)
	{
		e = extractMin(h);
		u = e->v;
		free(e);
		n = g->tab[u];
		// On met à jour la distance de tous les voisins
		while (n)
		{
			v = n->id;
			// Si la distance vers v n'est pas terminée et si la distance actuelle est plus courte que la précédente
			if (inMinHeap(h, v) && distance[u] != INT_MAX && n->weight + distance[u] < distance[v])
			{
				parent[v] = u;
				distance[v] = distance[u] + n->weight;
				decreaseKey(h, v, distance[v]);
			}
			n = n->next;
		}
	}
	destroyMinHeap(h);
	// Correction des chemins impossibles
	for (v = 0; v < g->size; v++)
		if (distance[v] == INT_MAX)
			parent[v] = INT_MAX; // reset valeur infini
}

// Affiche le chemin
/// Fonction utilitaire de displayDijkstraResults
void	renderPath(int *parent, int v)
{
	if (! parent) return;
	if (parent[v] == -1)
		return;
	renderPath(parent, parent[v]);
	printf("%2d ", v);
}

// Affiche le résultat de l'agorithme de Dijkstra
void	displayShortestPaths(int *distance, int *parent, int a, int n)
{
	if (! (distance && parent) || parent[a] != -1) return;
	// Affichage des distances et chemins
	printf("Distances from %2d:\n", a);
	for (int v = 0; v < n; v++)
	{
		printf("%2d → ", v);
		if (distance[v] != INT_MAX)
		{
			printf("%2d", distance[v]);
			if (v != a)
			{
				printf(" path: ");
				renderPath(parent, v);
			}
		}
		else
			printf("∞");
		putchar('\n');
	}
	// Affichage du tableau des pères
	printf("Table: [");
	for (int i = 0; i < n; i++)
	{
		if (parent[i] != INT_MAX)
			printf("%2d", parent[i]);
		else
			printf("∞");
		if (i + 1 < n)
			printf(", ");
	}
	printf("]\n");
}

// Affichage du graphe sur le terminal
void	displayGraph(Graph *g)
{
	if (! g) return;
	Node *n;
	
	printf("Format: vertex → link 1|weight 1 → ... → link n|weight n\n");
	for (int i = 0; i < g->size; i++)
	{
		n = g->tab[i];
		printf("%2d", i);
		if (! n)
			printf(" → \033[38;2;255;25;25mnull\033[0m"); // pas de voisins
		while (n)
		{
			printf(" → (%2d|%2d)", n->id, n->weight);
			n = n->next;
		}
		putchar('\n');
	}
}

// Libère la mémoire d'un graphe
void	destroyGraph(Graph *g)
{
	if (! g) return;
	Node *ncurr,*nnext;
	for(int i=0; i<g->size; i++)
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