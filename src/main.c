#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include "error.h"
#include "force.h"
#include "network.h"

int main()
{
	Graph *g;
	RootingTable *r;
	point_t *ptab = NULL;
	int *c = NULL; // 1 si c[i] doit etre coloré
	int **l = NULL;
	int clic[2] = {0}; //indices des nodes cliqués
	int update = 1, nbClics = 0, i, j;
	
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
	
	displayGraph(g);
	
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
						update = 1;
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
							printf("Distance between node %d to %d = %d\n", clic[0], clic[1], r[clic[0]].distance[clic[1]]);
						#endif
						nbClics++;
						update = 1;
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
					update = 1;
				}
			}
		}
		if (update) // pour optimiser les performances en évitant de mettre à jour l'affichage à chaque itération
		{
			sfRenderWindow_clear(window, sfBlack);
			displayGraph_sf(window,g,ptab,c,l);
			sfRenderWindow_display(window);
			update = 0;
		}
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
