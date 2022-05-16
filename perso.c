#include "Perso.h"
#include "fonctions.h"


void initPerso(Personne *p){
	(*p).position.x=722;
	(*p).position.y=577;
	(*p).position.w=50;
	(*p).position.h=50;
	(*p).initial=IMG_Load("personiv.png");
	(*p).etat=0;
}

void afficherPerso(Personne *p, SDL_Surface * screen){
	if((*p).etat==0){
		SDL_BlitSurface((*p).initial,NULL,screen,&(*p).position);
	}
	else if ((*p).etat>0 && (*p).etat<10){
		SDL_BlitSurface((*p).mouv[(*p).etat-1],NULL,screen,&(*p).position);
		(*p).etat++;	
	}
	else if ((*p).etat>10 && (*p).etat<20){
		SDL_BlitSurface((*p).saut[(*p).etat-11],NULL,screen,&(*p).position);
		(*p).etat++;		
	}
	else if ((*p).etat==10){
		SDL_BlitSurface((*p).mouv[(*p).etat-1],NULL,screen,&(*p).position);
		(*p).etat=1;
	}
	else if ((*p).etat==20){
		SDL_BlitSurface((*p).saut[(*p).etat-11],NULL,screen,&(*p).position);	
		(*p).etat=11;
	}
}

void deplacerPerso (Personne *p, int dt, int dir){
	switch(dir){
		case 1:
			(*p).position.x+=dt;
			break;
		case 2:
			(*p).position.x-=dt;
			break;
		case 3:
			(*p).position.y+=dt;
			break;
		case 4:
			(*p).position.y-=dt;
			break;
	}
}

void animerPerso (Personne* p){
	if ((*p).etat<1 || (*p).etat>10){
		(*p).etat=1;
	}
}

void saut (Personne* p){
	if ((*p).etat<11 || (*p).etat>20){
		(*p).etat=11;
	}
}

int distance_p(SDL_Rect a,SDL_Rect b){
	return (int)racine(carre(a.x-b.x)+carre(a.y-b.y));
}

int collisionBB(Personne J,Personne E){
    int c=0;
    if (distance_p(J.position,E.position)<35){
            c=1;
    }
    else{
        c=0;
    }
    return c;
}

void mort(Personne *p,Personne *a,Personne *b,Personne *c,Personne *d,time_t *start){
	*start = time( NULL);
	(*p).vies--;
	(*p).position.x=722;
	(*p).position.y=577;
	(*p).etat=0;

	(*a).position.x=782;
	(*a).position.y=445;
	(*a).vies=0;
	(*a).etat=0;
	(*b).position.x=782;
	(*b).position.y=445;
	(*b).vies=0;
	(*b).etat=0;
	(*c).position.x=782;
	(*c).position.y=445;
	(*c).vies=0;
	(*c).etat=0;
	(*d).position.x=782;
	(*d).position.y=445;
	(*d).vies=0;
	(*d).etat=0;
}

void mort_E(Personne *a,time_t *start){
	*start = time( NULL);

	(*a).position.x=782;
	(*a).position.y=445;
	(*a).vies=0;
	(*a).etat=0;
}

int collision(Personne J,Personne E,Personne E2,Personne E3,Personne E4){
	int c=0;
	c+=collisionBB( J, E);
	c+=collisionBB( J, E2);
	c+=collisionBB( J, E3);
	c+=collisionBB( J, E4);
	if (c==0){
		return c;
	}
	else{
		return 1;
	}
}
