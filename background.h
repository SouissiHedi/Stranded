#ifndef Backgroud_H
#define Backgroud_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "Perso.h"
#include "fonctions.h"

typedef struct {
	Mix_Music *son;
	SDL_Rect position;
	SDL_Rect zone;
	SDL_Surface *img;
	Image p_obj1;
	Image p_obj2;
	int direction;
}Background;



void initBack(Background * b);
void afficherBack(Background b, Personne P, SDL_Surface *screen);
int collisionBB_niv3(Personne J,Image E);
int collisionrocher(Personne J,Image E);
void animerBackground( Image * b);
int scrolling (Personne *P,int r,int l,int d,int u,SDL_Surface *mask);
void initanime(Image *b,Image *c);
int deplacercow(Image *h,Personne p);
void affichercow(Image h,Personne p,SDL_Surface *screen,int s);
void initp(Personne *p);
void afficherp(Personne p, SDL_Surface *ecran);
void animep(Personne *p,int r,int l,int d,int u);
void initArb(Image *a,Image *b,Image *c,Image *d);
void initRock (Image *r0,Image *r1,Image *r2,Image *r3);
void afficherArb(Image a,Personne p, SDL_Surface * screen,int h,Image d);
void afficher_all_Arb(Image a,Image b,Image c,Image d,Personne p, SDL_Surface * screen,int T[6]);
void afficher_all_Rk(Image r,Image r2,Image r3,Image r_c,Personne p, SDL_Surface * screen,int T[6]);
void inithouse(Image* h,Image *d);
void afficher_im(Image h,Personne p, SDL_Surface * screen);
void animedoor(Image *d);



#endif


