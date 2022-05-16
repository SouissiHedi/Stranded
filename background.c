#include "background.h"
#include "fonctions.h"


void initBack(Background * b){    
    b->img = IMG_Load("fond_niv3.png");
    b->position.x = 85;
    b->position.y = 90;
    b->zone.x=0;
    b->zone.y=0;
    b->zone.h=765;
    b->zone.w=1385;
    
}

void afficherBack(Background b, Personne P, SDL_Surface * screen){
	SDL_Rect aff;
	aff.x=P.position.x-693;
	aff.y=P.position.y-383;
	if(aff.y>5982){
		aff.y=5982;
	}
	if(aff.y<0){
		aff.y=0;
	}
	if(aff.x<0){
		aff.x=0;
	}
	if(aff.x>11536){
		aff.x=11536;
	}
	aff.h=b.zone.h;
	aff.w=b.zone.w;
	SDL_BlitSurface(b.img, &aff, screen, &b.position);
}

int collisionBB_niv3(Personne J,Image E){
    int c=0;
    if (distance_p(J.position,E.position)<35){
            c=1;
    }
    else{
        c=0;
    }
    return c;
}

int collisionrocher(Personne J,Image E){
    int c=0;
    if (distance_p(J.position,E.position)<45){
            c=1;
    }
    else{
        c=0;
    }
    return c;
}

void initanime(Image *b,Image *c){
    b->img=IMG_Load("bird.png");
    b->zone.x=0;
    b->zone.y=0;
    b->zone.w=179;
    b->zone.h=149;
    b->position.x=0;
    b->position.y=700;/*6365*/
    c->img=IMG_Load("cow.png");
    c->zone.x=0;
    c->zone.y=0;
    c->zone.w=197;
    c->zone.h=130;
    c->position.x=8000;
    c->position.y=500;
}


void affichercow(Image h,Personne p,SDL_Surface *screen,int s){
	SDL_Rect pos;
	if ((abso(p.position.x-h.position.x)<693 ||  p.position.x<693 )&& (abso(p.position.y-h.position.y)<383 ||  p.position.y<383 )){
		if(p.position.x>693){
			pos.x=h.position.x-p.position.x+693;
		}
		else{
			pos.x=h.position.x;
		}
		if(p.position.y>383){
			pos.y=h.position.y-p.position.y+383;
		}
		else{
			pos.y=h.position.y;
		}
		if (s==1){
			SDL_BlitSurface(h.img,&h.zone,screen,&pos);
		}
	}
}

int deplacercow(Image *h,Personne p){
	if(distance_p(p.position,(*h).position)<=800){
		if(abso((*h).position.x-p.position.x)>30 && (*h).position.x<p.position.x){
			(*h).position.x=(*h).position.x+15;
			(*h).zone.y=130;
			if ((*h).zone.x==394)
				(*h).zone.x=0;
			else
				(*h).zone.x=(*h).zone.x+197;
			return 1;
		}
		else if (abso((*h).position.x-p.position.x)>30 && (*h).position.x>p.position.x){
			(*h).position.x=(*h).position.x-15;
			(*h).zone.y=0;
			if ((*h).zone.x==394)
				(*h).zone.x=0;
			else
				(*h).zone.x=(*h).zone.x+197;
			return 1;
		}
		else if (abso((*h).position.y-p.position.y)>30 && (*h).position.y>p.position.y){
			(*h).position.y=(*h).position.y-15;
			(*h).zone.y=420;
			if ((*h).zone.x==394)
				(*h).zone.x=0;
			else
				(*h).zone.x=(*h).zone.x+197;
			return 1;
		}
		else if (abso((*h).position.y-p.position.y)>30 && (*h).position.y<p.position.y){
			(*h).position.y=(*h).position.y+15;
			(*h).zone.y=260;
			if ((*h).zone.x==394)
				(*h).zone.x=0;
			else
				(*h).zone.x=(*h).zone.x+197;
			return 1;
		}
	}
	return 0;
}


void animerBackground( Image * b){
	if ((*b).zone.x==358){
		(*b).zone.x=0;
	}
	else{
		(*b).zone.x=(*b).zone.x+179;
	}
	(*b).position.x=(*b).position.x+30;
	if ((*b).position.x>=12229){
		(*b).position.y=rand()%6360+1;
		(*b).position.x=0;
	}
}


int scrolling (Personne *P,int r,int l,int d,int u,SDL_Surface *mask){
	if (r==1){
		(*P).position.x=(*P).position.x+40;
		if (CollitionParfaitePersoB(mask,*P)!=0){
			(*P).position.x=(*P).position.x-40;
		}
		if ((*P).position.x>12159){
			(*P).position.x=12159;
		}
	}
	if (l==1){
		(*P).position.x=(*P).position.x-40;
		if (CollitionParfaitePersoB(mask,*P)!=0){
			(*P).position.x=(*P).position.x+40;
		}
		if ((*P).position.x<0){
			(*P).position.x=0;
		}
	}
	if (d==1){
		(*P).position.y=(*P).position.y+40;
		if (CollitionParfaitePersoB(mask,*P)!=0){
			(*P).position.y=(*P).position.y-40;
		}
		if ((*P).position.y>6259){
			(*P).position.y=6259;
		}
	}
	if (u==1){
		(*P).position.y=(*P).position.y-40;
		if (CollitionParfaitePersoB(mask,*P)!=0){
			(*P).position.y=(*P).position.y+40;
		}
		if ((*P).position.y<0){
			(*P).position.y=0;
		}
	}
	if(CollitionParfaitePerso(mask,*P)!=0){
		return 1;
	}
	return 0;
}

void initp(Personne *p){
    	p->initial=IMG_Load("perso3.png");
    	p->position.x=5500;
    	p->position.y=2900;
    	p->zone.w=70;
    	p->zone.h=106;
    	p->zone.x=70;
    	p->zone.y=0;
   

}
void afficherp(Personne p, SDL_Surface *ecran){
	SDL_Rect pos;
	if (p.position.x>693 && p.position.x<11536 && p.position.y>383 && p.position.y<5982){
		pos.x=658;
		pos.y=330;
	}
	else if (p.position.x<=693){
		if (p.position.y<=383){
			pos.x=p.position.x-35;
			pos.y=p.position.y-53;
		}
		else if (p.position.y>=5982){
			pos.x=p.position.x-35;
			pos.y=p.position.y+330-5982;
		}
		else {
			pos.y=330;
			pos.x=p.position.x-35;
		}
	}
	else if (p.position.x>=11536){
		if (p.position.y<=383){
			pos.y=p.position.y-53;
			pos.x=p.position.x-11536+692-35;
		}
		else if (p.position.y>=5982){
			pos.y=p.position.y+383-53-5982;
			pos.x=p.position.x-11536+692-35;
		}
		else {
			pos.y=330;
			pos.x=p.position.x-11536+692-35;
		}
	}
	else if (p.position.y<=383){
		pos.x=658;
		pos.y=p.position.y-53;
	}
	else if (p.position.y>=5982){
		pos.x=658;
		pos.y=p.position.y+330-5982;
	}
	if(pos.y>659){
		pos.y=659;
	}
	if(pos.y<0){
		pos.y=0;
	}
	if(pos.x<0){
		pos.x=0;
	}
	if(pos.x>1315){
		pos.x=1315;
	}
	SDL_BlitSurface(p.initial,&p.zone,ecran,&pos);
}

void animep(Personne *p,int r,int l,int d,int u){
	if (d==1){
		p->zone.y=0;
		if (p->zone.x==210){
                	p->zone.x=0;
                }
            	else{
                	p->zone.x=p->zone.x+70;
			SDL_Delay(100);
                }
        }
	else if (r==1){
            	p->zone.y=104;
		if (p->zone.x==210){
                	p->zone.x=0;
               	}
            	else{
                	p->zone.x=p->zone.x+70;
			SDL_Delay(100);
		}
        }
	else if (l==1){
		p->zone.y=208;
		if (p->zone.x==210)
			p->zone.x=0;
		else{
                	p->zone.x=p->zone.x+70;
			SDL_Delay(100);
		}
	}
        else if (u==1){
		p->zone.y=312;
           	if (p->zone.x==210)
			p->zone.x=0;
		else{
                	p->zone.x=p->zone.x+70;
			SDL_Delay(100);
		}
	}
	else{
		p->zone.x=70;
		p->zone.y=0;
	}
}


void initArb(Image *a,Image *b,Image *c,Image *d){
    a->img=IMG_Load("arb1.png");
    a->position.x=1000;
    a->position.y=900;   	
    b->img=IMG_Load("arb2.png");
    b->position.x=1300;
    b->position.y=1200;   	
    c->img=IMG_Load("arb3.png");
    c->position.x=1200;
    c->position.y=1500;  	
    d->img=IMG_Load("arb0.png");
    d->position.x=0;
    d->position.y=0;
}

void afficherArb(Image a,Personne p, SDL_Surface * screen,int h,Image d){
	SDL_Rect pos;
	if ((abso(p.position.x-a.position.x)<693 ||  p.position.x<693 )&& (abso(p.position.y-a.position.y)<383 ||  p.position.y<383 )){
		if(p.position.x>693){
			pos.x=a.position.x-p.position.x+693;
		}
		else{
			pos.x=a.position.x;
		}
		if(p.position.y>383){
			pos.y=a.position.y-p.position.y+383;
		}
		else{
			pos.y=a.position.y;
		}
		if (h==1){
			SDL_BlitSurface(a.img,NULL,screen,&pos);
		}
		else{
			SDL_BlitSurface(d.img,NULL,screen,&pos);
		}
	}
}

void afficher_all_Arb(Image a,Image b,Image c,Image d,Personne p, SDL_Surface * screen,int T[6]){
	afficherArb(a,p,screen,T[0],d);
	afficherArb(b,p,screen,T[1],d);
	afficherArb(c,p,screen,T[2],d);
}

void afficher_all_Rk(Image r,Image r2,Image r3,Image r_c,Personne p, SDL_Surface * screen,int T[6]){
	afficherArb(r,p,screen,T[3],r_c);
	afficherArb(r2,p,screen,T[4],r_c);
	afficherArb(r3,p,screen,T[5],r_c);
}

void initRock (Image *r0,Image *r1,Image *r2,Image *r3){   	
    	r0->img=IMG_Load("rock.png");
    	r0->position.x=5500;
    	r0->position.y=3200;
	r1->img=IMG_Load("rock.png");
    	r1->position.x=5000;
    	r1->position.y=3000;
	r2->img=IMG_Load("rock.png");
    	r2->position.x=5300;
    	r2->position.y=2800;
	r3->img=IMG_Load("rock_B.png");
    	r3->position.x=0;
    	r3->position.y=0;
}

void inithouse(Image* h,Image *d){
	h->img=IMG_Load("house1.png");
	h->position.x=6969;
	h->position.y=5000;
    	h->zone.w=350;
    	h->zone.h=460;
    	h->zone.x=0;
    	h->zone.y=0;
	d->img=IMG_Load("door.png");
	d->position.x=7049;
    	d->position.y=5322;
    	d->zone.w=115;
    	d->zone.h=134;
    	d->zone.x=0;
    	d->zone.y=0;
}

void afficher_im(Image h,Personne p, SDL_Surface * screen){
	SDL_Rect pos;
	if ((abso(p.position.x-h.position.x)<693 ||  p.position.x<693 )&& (abso(p.position.y-h.position.y)<383 ||  p.position.y<383 )){
		if(p.position.x>693){
			pos.x=h.position.x-p.position.x+693;
		}
		else{
			pos.x=h.position.x;
		}
		if(p.position.y>383){
			pos.y=h.position.y-p.position.y+383;
		}
		else{
			pos.y=h.position.y;
		}
		SDL_BlitSurface(h.img,&h.zone,screen,&pos);
	}
}

void animedoor(Image *d){
	(*d).zone.x=0;
	if ((*d).zone.y==670){
		(*d).zone.y=0;
	}
	else{
		(*d).zone.y=(*d).zone.y+134;
	}
}











