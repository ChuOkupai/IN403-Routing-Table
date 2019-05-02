#include <stdlib.h>
#include <time.h>
#include "error.h"
#include "network.h"

// Création d'une arête entre 2 sommets
/// Le poids doit être supérieur à 0 !
void LINK(Graph *g, int a, int b, int w)
{
	link(g, a, b, w);
	link(g, b, a, w);
}

// Supprime une arête entre 2 sommets
void UNLINK(Graph *g, int a, int b)
{
	rmlink(g, a, b);
	rmlink(g, b, a);
}

void recut(Graph *g, const int a, const int b)
{
	int c,d;
	do
		c = rand() % (T2_END-T2_START) + T2_START;
	while (a == c || b == c || linked(g,a,c) || linked(g,b,c));
	Node *n = g->tab[a];
	while(n->id < T2_START)
		n = n->next;
	d = n->id;
	UNLINK(g,c,d);
	LINK(g,a,c,rand()%11+10);
	LINK(g,b,d,rand()%11+10);
}

void initTier1(Graph *g)
{
	int i, j;
	for (i = 0; i < T1_END; i++)
		for (j = i + 1; j < T1_END; j++)
			if (rand() % 4)
				LINK(g, i, j, rand() % 6 + 5);
}


void initTier2(Graph *g)
{
	int d[20] = { 0 }, i, j, k, n;

	
	for (i = T2_START; i < T2_END; i++)
	{
		// Liaison au Tier 1
		j = 0;
		k = rand() % 2 + 1;
		while (j < k)
		{
			n = rand() % T1_END;
			if (linked(g, i, n))
				continue;
			LINK(g, i, n, rand() % 11 + 10);
			j++;
		}
	}
	
	//Liaison Tier 2 degré 1
	for(i = T2_START; i < T2_END; i++)
	{
		if(d[i-T2_START] == 0)
		{
			do
				n = rand() % (T2_END-T2_START) + T2_START;
			while (i == n || d[n-T2_START] > 0);
			LINK(g, i, n, rand() % 11 + 10);
			d[i-T2_START]++;
			d[n-T2_START]++;
		}
	}
	
	//Liaison Tier 2 degré 2
	int b,nblink = 0;
	for(i = T2_START; i < T2_END; i++)
	{
		if(d[i-T2_START] == 1)
		{
			if(nblink == 9)
			{
				b = T2_START;
				while(d[b-T2_START] != 1 || b == i)
				{
					b++;
				}
				printf("b: %d\n", b);
				if(linked(g,i,b))
				{
					printf("RECUT i: %d\n", i);
					recut(g,i,b);
					d[i-T2_START]++;
					d[b-T2_START]++;
				}
				
				else
				{
					printf("%d PAS LINK : %d\n", i, b);
					LINK(g,i,b,rand()%11 +10);
					d[i-T2_START]++;
					d[b-T2_START]++;
				}
				break;
			}
			do
			{
				n = rand() % (T2_END-T2_START) + T2_START;
				printf("i: %d n: %d\n", i, n);
			}
			while (i == n || d[n-T2_START] > 1 || linked(g,i,n));
			LINK(g, i, n, rand() % 11 + 10);
			d[i-T2_START]++;
			d[n-T2_START]++;
			nblink++;
		}
		for(int j=0;j<20;j++)
			printf("J%d : %d\n", j+T2_START, d[j]);
	}
	for(int j=0;j<20;j++)
			printf("J%d : %d\n", j+T2_START, d[j]);
}

void initTier3(Graph *g)
{
	int i, j, n;
	
	// Liaison au Tier 2
	for (i = T3_START; i < T3_END; i++)
		for (j = 0; j < 2; j++)
		{
			do
				n = rand() % (T2_END-T2_START) + T2_START;
			while (linked(g, i, n));
			LINK(g, i, n, rand() % 36 + 15);
		}
	// Liaison au Tier 3
	for (i = T3_START; i < T3_END; i++)
		if (! g->tab[i]->next->next)
		{
			do
				n = rand() % (T3_END-T3_START) + T3_START;
			while (i == n || g->tab[n]->next->next);
			LINK(g, i, n, rand() % 36 + 15);
		}
}

// Crée le réseau
Graph*	createNetwork()
{
	Graph *g = NULL;
	
	srand(time(NULL));
	// tant que le réseau n'est pas connexe
	while (! depthFirstSearch(g))
	{
		destroyGraph(g);
		g = newGraph(SIZE);
		initTier1(g);
		initTier2(g);
		initTier3(g);
	}
	return g;
}

// Crée la table de routage en calculant les chemins
RootingTable*	createRootingTable(const Graph *g)
{
	RootingTable *r;
	
	CHECK(r = (RootingTable*)malloc(g->size * sizeof(RootingTable)));
	for (int i = 0; i < g->size; i++)
	{
		CHECK(r[i].distance = (uint8_t*)malloc(g->size * sizeof(uint8_t)));
		CHECK(r[i].parent = (int8_t*)malloc(g->size * sizeof(int8_t)));
		dijkstra(g, r[i].distance, r[i].parent, i);
	}
	return r;
}

// Libère la mémoire de la table de routage
void	destroyRootingTable(RootingTable *r)
{
	if (! r) return;
	for (int i = 0; i < SIZE; i++)
	{
		free(r[i].distance);
		free(r[i].parent);
	}
	free(r);
}
