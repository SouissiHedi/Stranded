#ifndef MiniMap_H
#define MiniMap_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "fonctions.h"

typedef struct {
  SDL_Surface * img;
  SDL_Rect pos;
  SDL_Surface * img_pers;
  SDL_Rect pos_pers;
}minimap;


/*
int nbJoueur(char nomFich[]);
joueur * charger_donnees(char nomFich[], int * n);
int trouver(joueur * tab, char nom[], int n);
joueur * ajouter (joueur v, joueur * tab, int * n);
void saisirJ (joueur * ptv,int score);
void affScore(joueur * tab, int n);
*/

void initminimap( minimap * m);
void MAJMinimap(SDL_Rect posJoueur , minimap * m);
void afficherminimap (minimap m, time_t start, SDL_Surface * screen,int score,int vies);
void sauvegarder(joueur * tab, FILE* F,int n);
void aff_inv(Image l,Image r,Image b,Image p,SDL_Surface* ecran,int nb,int nr,int np);
void meilleur(joueur * tab, int *score, char nomjoueur[],int n);

#endif
