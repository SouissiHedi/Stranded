# ifndef HEADER_H_INCLUDED
# define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
/**
  *@file enigme.h
  *@brief Testing Program.
  *@author C Team
  *@version 0.1
  *date Apr 28, 2022
  *
  *Testing programe for enigme
  scrollilng *
  */

typedef struct{
	SDL_Surface *img;
	SDL_Rect posp;
	SDL_Rect poscr;
}enigme;

typedef struct{
	SDL_Rect posp;
	SDL_Rect poscr;
}posi;

typedef struct{
	SDL_Surface *img;
	SDL_Rect position;
	SDL_Rect zone;
}Im;

typedef struct{
	SDL_Surface *img;
	posi posi[7];
	int p;
}animat;



void initenigme(enigme *e,enigme *e2,enigme *e3,char *nomfich[]);
void afficherenigme(int alea,enigme e, animat z[], SDL_Surface *screen,int anim);
void afficherselec(enigme e,enigme e2,enigme e3, SDL_Surface *screen,int aff);
void initanimation(animat z[]);
void animer (animat z[]);
int enigmealea(SDL_Surface *screen);

#endif
