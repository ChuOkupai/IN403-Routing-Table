#ifndef _FORCE_H
#define _FORCE_H

#include "graph.h"
#include "network.h"
#include <SFML/Graphics.h>
#include <SFML/System.h>

//Structure vecteur
typedef struct
{
	int x;
	int y;
} point_t;

typedef struct
{
	double force;
	double angle;
} vect_t;

double bearing_angle(point_t A, point_t B);

void randomize_points(point_t *tab, int n);

void displayGraph_sf(sfRenderWindow *window, Graph *g,point_t *tab,int *c,int **l);

void force_directed(sfRenderWindow *window,Graph *g,point_t *ptab,int *c,int **l);

int node_clic(point_t *tab, int x, int y, int n);

void color_the_way(int *c,int **l,const int8_t *parent,int b);

#define ABS(x) ((x)<0?(-x):(x))

#define K_COULOMB 5000000

#define K_HOOKE 0.2

#define DAMPING 0.1

#define SPRING_LEN 30

#define SCREEN_Y 720

#define SCREEN_X 1280

#define N_RADIUS 8

#endif