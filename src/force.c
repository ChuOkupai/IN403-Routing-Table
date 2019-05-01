#include "force.h"
#include "graph.h"
#include "error.h"
#include "network.h"
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

// Calcul la distance de A a B
double distance(point_t A, point_t B)
{	
	int dx = B.x - A.x;
	int dy = B.y - A.y;
	return sqrt(dx*dx + dy*dy);
}

// Renvoi l'indice du Node cliqué
int node_clic(point_t *tab, int x, int y, int n)
{
	point_t clic = {x,y};
	for(int i = 0; i < n; i++)
	{
		if(distance(tab[i],clic) <= N_RADIUS)
			return i;
	}
	return -1;
}

// Remplit le tableau des node a colorer si ils font parti du plus court chemin
void color_the_way(int *c,int **l,const int8_t *parent,int b)
{
	if(!parent) return;
	if(parent[b] == -1) return;
	color_the_way(c,l,parent,parent[b]);
	l[b][parent[b]] = 1;
	l[parent[b]][b] = 1;
	c[b] = 1;
}

// Calcul l'angle par rapport au nord
double bearing_angle(point_t A, point_t B)
{
	int dx = B.x - A.x;
	int dy = B.y - A.y;
	double deg = 90 - (180/M_PI)*atan2(dy,dx);
	return (deg >= 180 ? deg - 360 : deg);
}

// Calcul la force de repulsion entre le node A et B
vect_t rep_force(point_t A, point_t B)
{
	double dist = distance(A,B);
	double prox = (dist < 1 ? 1 : dist);

	//Loi de Coulomb F=k(Q1Q2/r^2)
	//K_CONST = k*Q1*Q2
	double force = -((double)K_COULOMB / (double)(prox*prox) );
	double angle = bearing_angle(A,B);

	return (vect_t){force,angle};
}

// Calcul la force d'attraction entre le node A et B
vect_t att_force(point_t A, point_t B, double ressort)
{
	double dist = distance(A,B);
	double prox = (dist < 1 ? 1 : dist);

	double force = (K_HOOKE * (prox - ressort < 0 ? 0 : prox - ressort) );

	double angle = bearing_angle(A,B);

	return (vect_t){force,angle};
}

// Donne des coordonnées aleatoires a chaque node
void randomize_points(point_t *tab, int n)
{
	for(int i = 0; i < n; i++)
	{
		tab[i].x = rand()%( SCREEN_X - 2*N_RADIUS) + N_RADIUS;
		tab[i].y = rand()%( SCREEN_Y - 2*N_RADIUS) + N_RADIUS;
	}
}

// Transforme les coordonnées circulaires en coordonnées carthesiennes
int get_force_x(vect_t A)
{ return (int)A.force*cos( (M_PI/180)*(90 - A.angle) ); }

int get_force_y(vect_t A)
{ return (int)A.force*sin( (M_PI/180)*(90 - A.angle) ); }

// Ajoute deux vecteurs de force
vect_t force_add(vect_t A, vect_t B)
{
	point_t sum1,sum2,ret;
	sum1 = (point_t){get_force_x(A),get_force_y(A)};
	sum2 = (point_t){get_force_x(B),get_force_y(B)};
	
	ret.x = sum1.x + sum2.x;
	ret.y = sum1.y + sum2.y;

	point_t origin = (point_t){0,0};
	double force = distance(origin,ret);
	double angle = bearing_angle(origin,ret);

	return (vect_t){force,angle};
}

// Affiche le graphe
void displayGraph_sf(sfRenderWindow *window, Graph *g,point_t *tab,int *c,int **l)
{
	sfCircleShape *circle[g->size];
	for(int i = 0; i < g->size; i++)
	{
		//setting the nodes
		circle[i] = sfCircleShape_create();
		sfCircleShape_setRadius(circle[i],N_RADIUS);

		sfVector2f center = {N_RADIUS,N_RADIUS};
		sfCircleShape_setOrigin(circle[i],center);

		sfVector2f coord = {tab[i].x,tab[i].y};
		sfCircleShape_setPosition(circle[i],coord);
		if(c[i] == 1)
		{
			sfCircleShape_setFillColor(circle[i],sfWhite);
		}
		else
		{
			if( i < T1_END )
				sfCircleShape_setFillColor(circle[i],sfColor_fromRGB(255,0,0));
			else if( i < T2_END )
				sfCircleShape_setFillColor(circle[i],sfColor_fromRGB(255,127,0));
			else 
				sfCircleShape_setFillColor(circle[i],sfColor_fromRGB(255,255,0));
		}
	}


	for(int i = 0; i < g->size; i++)
	{
		for(int j = 0; j < g->size; j++)
		{
			int rv = linked(g,i,j);
			if(rv)
			{	
				sfVector2f A = {tab[i].x,tab[i].y};
				sfVector2f B = {tab[j].x,tab[j].y};
				
				sfVertex line[2];
				line[0].position = A;
				line[1].position = B;
				if(l[i][j] == 1)
				{
					line[0].color = sfWhite;
					line[1].color = sfWhite;
				}
				else
				{
					line[0].color = sfColor_fromRGB(127-2*rv,255-4*rv,127-2*rv);
					line[1].color = sfColor_fromRGB(127-2*rv,255-4*rv,127-2*rv);
				}

				sfRenderWindow_drawPrimitives(window,line,2,sfLines,NULL);
			}
		}
	}

	for(int i = 0; i < g->size; i++)
	{
		sfRenderWindow_drawCircleShape(window,circle[i],NULL);
		sfCircleShape_destroy(circle[i]);
	}

}

// Trouve les coordonnées max en x et y atteintes par des nodes du graph
point_t coord_max(point_t *tab,int n)
{
	point_t max = {0,0};
	for(int i = 0; i < n; i++)
	{
		if(max.x < tab[i].x) max.x = tab[i].x;
		if(max.y < tab[i].y) max.y = tab[i].y;
	}
	
	return max;
}

// Trouve les coordonnées min en x et y atteintes par des nodes du graph
point_t coord_min(point_t *tab,int n)
{
	point_t min = {UCHAR_MAX,UCHAR_MAX};
	for(int i = 0; i < n; i++)
	{
		if(min.x > tab[i].x) min.x = tab[i].x;
		if(min.y > tab[i].y) min.y = tab[i].y;
	}
	return min;
}

/**
 *	Algorithme d'affichage du Graph
 *	Il calcul pour chaque node son vecteur de mouvement en fonction
 *	des nodes voisins et des nodes reliés.
 *	Il deplace ensuite chaque node et recommence jusqu'a ce que le graph se stabilise
 */
void force_directed(sfRenderWindow *window,Graph *g,point_t *ptab,int *c,int **l)
{
	vect_t velocity[g->size];
	point_t new_coord[g->size];
	
	for(int i = 0; i < g->size; i++)
	{
		velocity[i] = (vect_t){0,0};
		new_coord[i] = (point_t){0,0};
	}

	int iterations = 0;
	uint64_t count = 0;
	while(iterations < 10000)
	{
		int totDisp = 0;
		for(int i = 0; i < g->size; i++)
		{
			vect_t netForce = (vect_t){0,0};
			for(int j = 0; j < g->size; j++)
			{
				if(j == i) continue;
				netForce = force_add(netForce,rep_force(ptab[i],ptab[j]));
			}
			for(int j = 0; j < g->size; j++)
			{
				if(j == i) continue;
				if(linked(g,i,j))
					netForce = force_add(netForce,att_force(ptab[i],ptab[j],SPRING_LEN));
			}
			velocity[i] = force_add(velocity[i],netForce);
			velocity[i].force *= DAMPING;

			new_coord[i].x = ptab[i].x + get_force_x(velocity[i]);
			new_coord[i].y = ptab[i].y + get_force_y(velocity[i]);
		}
		for(int i = 0; i < g->size; i++)
		{
			int add = ABS( (new_coord[i].x - ptab[i].x) );
			totDisp += add;
			ptab[i].x = new_coord[i].x;
			ptab[i].y = new_coord[i].y;	
		}
		
			
			
		sfRenderWindow_clear(window, sfBlack);
	
		displayGraph_sf(window,g,ptab,c,l);
		
		sfRenderWindow_display(window);
		
		if(totDisp <= 5 && totDisp >= 0) count++;
		if(totDisp < 0) 
		{
			printf("Overflow de totDisp\n");
			exit(EXIT_FAILURE);
		}
		if(count >= 20) break;
		iterations++;

	}

		//rescaling pour afficher au centre
		//calcul de T vecteur pour que le milieu soit celui de l'ecran
		point_t max = coord_max(ptab,g->size);
		point_t min = coord_min(ptab,g->size);
		point_t T = { SCREEN_X/2 - (max.x + min.x)/2, SCREEN_Y/2 - (max.y + min.y)/2 };
		
		//calcul de la transformation uniforme pour deZoomer
		//sous la forme Ax+B
		//A = J
		//B = M*(J-1)
		double Mx = SCREEN_X/2;
		double Jx = Mx/(double)( (max.x + T.x) - Mx);
		double Bx = -Mx*(Jx-1);
		
		double My = SCREEN_Y/2;
		double Jy = My/( (max.y + T.y) - My);
		double By = -My*(Jy-1);
		
		for(int i = 0; i < g->size; i++)
		{
			ptab[i].x += T.x;
			ptab[i].x = Jx*ptab[i].x + Bx;
			ptab[i].y += T.y;
			ptab[i].y = Jy*ptab[i].y + By;
		}
	sfRenderWindow_clear(window, sfBlack);

	displayGraph_sf(window,g,ptab,c,l);
	
	sfRenderWindow_display(window);


}