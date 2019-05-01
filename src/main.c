#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "error.h"
#include "force.h"
#include "network.h"

// Gestion du debug
/// activé si valeur non nulle
#define DEBUG 1

int main()
{
	Graph *g;
	RootingTable *r;
	point_t *ptab = NULL;
	int *c = NULL; // 1 si c[i] doit etre coloré
	int **l = NULL;
	int clic[2] = {0}; //indices des nodes cliqués
	int nbClics = 0, i, j;
	
	g = createNetwork();
	r = createRootingTable(g);
	
	CHECK(ptab = (point_t*)malloc(sizeof(point_t)*g->size));
	randomize_points(ptab,g->size);
	
	CHECK(c = (int*)malloc(sizeof(int)*g->size));
	CHECK(l = (int**)malloc(sizeof(int *)*g->size));
	for(i = 0; i < g->size; i++)
	{	
		CHECK(l[i] = (int*)malloc(sizeof(int)*g->size));
		for(j = 0; j < g->size; j++)
			l[i][j] = 0;
		c[i] = 0;
	}
	
	#if DEBUG
		displayGraph(g);
		// Affichage des chemins possibles pour le premier noeud
		displayShortestPaths(r[0].distance, r[0].parent, 0, g->size);
	#endif
	
	printf("## Le graphe devient plus grand que l'ecran durant l'algorithme d'affichage\n Il sera redimensionne a la fin\n");
	printf("Par contre, si le graphe s'en va tres vite c'est qu'il y a eu un probleme\n");
	//partie SFML
	sfVideoMode mode = {SCREEN_X,SCREEN_Y,32};
	sfRenderWindow* window;
	sfEvent event;
	
	//main window
	window = sfRenderWindow_create(mode, "IN403-Rooting-Table", sfClose, NULL);
	if(!window)
		exit(EXIT_FAILURE);
	
	
	//Main loop
	force_directed(window,g,ptab,c,l);
	while(sfRenderWindow_isOpen(window))
	{
		//event loop
		while(sfRenderWindow_pollEvent(window, &event))
		{
			if(event.type == sfEvtClosed)
				sfRenderWindow_close(window);

			if(event.type == sfEvtMouseButtonPressed)
			{
				if(nbClics == 0)
				{
					clic[0] = node_clic(ptab,event.mouseButton.x,event.mouseButton.y,g->size);
					if(clic[0] != -1)
					{
						c[clic[0]] = 1;
						nbClics++;
					}
					else
						clic[0] = 0;
				} 
				else if(nbClics == 1)
				{
					clic[1] = node_clic(ptab,event.mouseButton.x,event.mouseButton.y,g->size);
					
					if(clic[1] != -1)
					{
						c[clic[1]] = 1;
						
						color_the_way(c,l,r[clic[0]].parent,clic[1]);
						#if DEBUG
							printf("distance between node %d to %d = %d\n", clic[0], clic[1], r[clic[0]].distance[clic[1]]);
						#endif
						nbClics++;
					}
					else
						clic[1] = 0;
				}
				else 
				{
					for(i = 0; i < g->size; i++)
					{
						c[i] = 0;
						for(j = 0; j < g->size; j++)
							l[i][j] = 0;
					}
					clic[0] = clic[1] = 0;
					nbClics = 0;
				}
			}
		}
		
		sfRenderWindow_clear(window, sfBlack);
		
		displayGraph_sf(window,g,ptab,c,l);
		
		sfRenderWindow_display(window);
	}
	
	sfRenderWindow_destroy(window);
	//fin partie SFML
	
	free(ptab);
	free(c);
	for(i = 0; i < g->size; i++)
		free(l[i]);
	free(l);
	destroyGraph(g);
	destroyRootingTable(r);
	return 0;
}