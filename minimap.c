#include "minimap.h"
#include "Perso.h"
#include "fonctions.h"
#include "background.h"


void initminimap( minimap * m){
	(*m).img=IMG_Load("mini.png");
	(*m).img_pers=IMG_Load("mini_pers.png");
	(*m).pos.x=10;
	(*m).pos.y=10;
	(*m).pos_pers.x=100;
	(*m).pos_pers.y=50;
}

void MAJMinimap(SDL_Rect posJoueur , minimap * m){
	(*m).pos_pers.x=10+(int)(300*posJoueur.x/12229);
	(*m).pos_pers.y=10+(int)(156*posJoueur.y/6365);
}

void afficherminimap (minimap m, time_t start, SDL_Surface * screen,int score,int vies){
	SDL_Surface *Text=NULL;
	SDL_Rect postxt;
	SDL_BlitSurface(m.img,NULL,screen,&m.pos);
	SDL_BlitSurface(m.img_pers,NULL,screen,&m.pos_pers);
	time_t end = time( NULL);
    	unsigned long secondes = (unsigned long) difftime( end, start );
   	int min = (int) (secondes/60);
	int sec = (int) secondes % 60;
	int length = snprintf( NULL, 0, "Score : %d | %d : %d",score, min, sec);
	char* str = malloc( length + 1 );
	snprintf( str, length + 1, "Score : %d | %d : %d",score, min, sec );
	TTF_Font *police=NULL;
	SDL_Color couleur={255,255,255};
	police = TTF_OpenFont("Ubuntu-MI.ttf",40);
	Text = TTF_RenderText_Blended(police,str,couleur);
	postxt.x=1200;
	postxt.y=10;
	SDL_BlitSurface(Text,NULL,screen, &postxt);
	free(str);
	length = snprintf( NULL, 0, "Vies : %d",vies);
	char* str2 = malloc( length + 1 );
	snprintf( str2, length + 1, "Vies : %d",vies);
	Text = TTF_RenderText_Blended(police,str2,couleur);
	postxt.x=800;
	SDL_BlitSurface(Text,NULL,screen, &postxt);
	free(str2);
}

void sauvegarder(joueur * tab,FILE* F,int n){
	for (int i=0;i<n;i++){
		fseek(F,0,SEEK_END);
		fprintf(F,"%s : %d;",tab[i].nom,tab[i].score);
    	}
}

void aff_inv(Image l,Image r,Image b,Image p,SDL_Surface* ecran,int nb,int nr,int np){
	SDL_Surface *Text=NULL;	
	TTF_Font *police=NULL;
	SDL_Color couleur={255,255,255};
	SDL_Rect postxt;
	char* str = malloc(6);
	police = TTF_OpenFont("Ubuntu-MI.ttf",35);
	if (nb==3 && nr ==3){
		postxt.x=1305;
		postxt.y=180;
		if(np==1){
			couleur.r=0;
			couleur.b=0;
		}
		snprintf( str, 6,  "%d / 1",np);
		SDL_BlitSurface(l.img,NULL,ecran, &l.position);
		SDL_BlitSurface(p.img,NULL,ecran, &p.position);
		Text = TTF_RenderText_Blended(police,str,couleur);
		SDL_BlitSurface(Text,NULL,ecran, &postxt);
	}
	else{
		SDL_BlitSurface(r.img,NULL,ecran, &r.position);
		SDL_BlitSurface(b.img,NULL,ecran, &b.position);
		postxt.x=1300;
		postxt.y=120;
		if(nr==3){
			couleur.r=0;
			couleur.b=0;
		}
		snprintf( str, 6,  "%d / 3",nr);
		Text = TTF_RenderText_Blended(police,str,couleur);
		SDL_BlitSurface(Text,NULL,ecran, &postxt);
		snprintf( str, 6,  "%d / 3",nb);
		postxt.y=postxt.y+57;
		if(nb==3){
			couleur.r=0;
			couleur.b=0;
		}
		else{
			couleur.r=255;
			couleur.b=255;
		}
		Text = TTF_RenderText_Blended(police,str,couleur);
		SDL_BlitSurface(Text,NULL,ecran, &postxt);
	}
	SDL_FreeSurface(Text);
	free(str);
}

void meilleur(joueur * tab, int *score, char nomjoueur[],int n){
	int max=0,pos=0;
	for (int i=0;i<n;i++){
		if (tab[i].score>max){
			max=tab[i].score;
			pos=i;
		}
    	}
	*score=tab[pos].score;
	strcpy(nomjoueur,tab[pos].nom);
}



/**

init minimmap
MAJ minimap
afficher minimap
gestion de temps (enigme, jeu)
"meilleur score:
 - entrer le nom du joueur au debut de chaque partie
 -sauvegarder le score a la fin de chaque partie 
-dans options menu: afficher le meilleur score et son proprietaire"

typedef struct {
  SDL_Surface * img;
  SDL_Rect pos;
  SDL_Surface * img_pers;
  SDL_Rect pos_pers;
}minimap;

**/
