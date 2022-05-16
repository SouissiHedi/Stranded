#ifndef Perso_H
#define Perso_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

typedef struct {
	SDL_Rect position;
	SDL_Rect zone;
	SDL_Surface *initial;
	SDL_Surface *mouv[10];
	SDL_Surface *saut[10];
	int etat;
	int vies;
	int direction;
}Personne;


void initPerso(Personne *p);
void afficherPerso(Personne *p, SDL_Surface * screen);
void deplacerPerso (Personne *p, int dt, int dir);
void animerPerso (Personne* p);
void saut (Personne* p);
void mort(Personne *p,Personne *a,Personne *b,Personne *c,Personne *d,time_t *start);
void mort_E(Personne *a,time_t *start);
int distance_p(SDL_Rect a,SDL_Rect b);
int collisionBB(Personne J,Personne E);
int collision(Personne J,Personne E,Personne E2,Personne E3,Personne E4);

#endif
