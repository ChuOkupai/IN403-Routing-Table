#include <stdlib.h>
#include <time.h>
#include "error.h"
#include "network.h"

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

	//init sommet degré 2 Tier 2
	for(i=0;i<20;i++) d[i] = 2;
	
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
		// Liaison au Tier 2
		// NE MARCHE PAS DANS CERTAINS PETITS CAS
		/// Il faut traiter tous les sommets quand tu ajoutes une arête pour corriger le tier 2
		/// Donc 3 boucles, une pour chaque degré et la dernière tirage random
		k = rand()%2 ? k+1 : k;
		k -= d[i-T2_START];
		
		j = 0;
		while (j < k)
		{
			n = rand() % (T2_END-T2_START) + T2_START;
			if (i != n && d[n-T2_START] < 3 && d[i-T2_START] < 3 && !linked(g, i, n))
			{
				LINK(g, i, n, rand() % 11 + 10);
				d[n-T2_START]++;
				d[i-T2_START]++;
				j++;
			}
		}
	}
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
	
	CHECK(r = (RootingTable*)malloc(SIZE * sizeof(RootingTable)));
	for (int i = 0; i < SIZE; i++)
	{
		CHECK(r[i].distance = (uint8_t*)malloc(SIZE * sizeof(uint8_t)));
		CHECK(r[i].parent = (int8_t*)malloc(SIZE * sizeof(int8_t)));
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