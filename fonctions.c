#include "fonctions.h"
#include "Perso.h"
#include "background.h"
#include "minimap.h"
#include "enigme.h"


float carre(int a){
	return (float)(a*a);
}

int abso(int a){
	if (a<0){
		return -a;
	}
	else{
		return a;
	}
}

float racine(float a){
	float M,n,c,b;
	if(a==0.0) {
		return 0.0;
	}
	else{
		M=1.0;
		n=a;
		while(n>=2.0) {
			n=0.25*n;
			M=2.0*M;
		}
		while(n<0.5) {
			n=4.0*n;
			M=0.5*M;
		}
		c=n;
		b=1.0-n;
		do {
			c=c*(1.0+0.5*b);
			b=0.25*(3.0+b)*b*b;
		}while(b>=1.0E-15);
		return (c*M);
	}
}

int nbJoueur(char nomFich[]){
	joueur v;
	int a=0;
	fseek(nomFich,0,SEEK_SET);
	while(fscanf(nomFich,"%s : %d;",v.nom,&v.score)!=EOF){
		a++;
	}
	return a;
}

void charger_donnees(FILE* F, int * n,joueur tab[]){
   	*n = nbJoueur(F);
   	fseek(F,0,SEEK_SET);
	for(int y=0;y<(*n);y++){
       		fscanf(F,"%s : %d;",tab[y].nom,&tab[y].score);
	}
}

int trouver(joueur * tab, char nom[], int n){
    int ind=-1;
    for(int i=0;i<n;i++){
        if(strcmp(nom,tab[i].nom)==0){
            ind=i;
        }
    }
    return ind;
}

void ajouter (joueur v, joueur tab[], int * n){
	if((*n)<20){
		tab[*n]=v;
		(*n)++;
	}
	else{
		printf("plus d\x27""espace\n");
	}
}

void saisirJ (joueur * ptv,int score,SDL_Surface *ecran){
	SDL_Surface *img,*Text=NULL;
	SDL_Rect aff,postxt;
	img=IMG_Load("nomaff.png");
	aff.x=607;
	aff.y=393;
	TTF_Font *police=NULL;
	SDL_Color couleur={0,0,0};
	police = TTF_OpenFont("Ubuntu-MI.ttf",30);
	postxt.x=610;
	postxt.y=420;
	int read=1,max=0;
	char s[21];
	SDL_Event evento;
	while(read && max<20){
		SDL_BlitSurface(img,NULL,ecran,&aff);
		Text = TTF_RenderText_Blended(police,s,couleur);
		SDL_BlitSurface(Text,NULL,ecran, &postxt);
		SDL_Flip(ecran);
		while(SDL_PollEvent(&evento)){
			switch(evento.type){
				case SDL_QUIT:
					read=0;
					break;
				case SDL_KEYDOWN:
					switch(evento.key.keysym.sym){
						case SDLK_KP_ENTER:
						case SDLK_RETURN:
						case SDLK_ESCAPE:
							read =0;
							break;
						case SDLK_a:
							s[max]='a';
							max++;
							break;
						case SDLK_b:
							s[max]='b';
							max++;
							break;
						case SDLK_c:
							s[max]='c';
							max++;
							break;
						case SDLK_d:
							s[max]='d';
							max++;
							break;
						case SDLK_e:
							s[max]='e';
							max++;
							break;
						case SDLK_f:
							s[max]='f';
							max++;
							break;
						case SDLK_g:
							s[max]='g';
							max++;
							break;
						case SDLK_h:
							s[max]='h';
							max++;
							break;
						case SDLK_i:
							s[max]='i';
							max++;
							break;
						case SDLK_j:
							s[max]='j';
							max++;
							break;
						case SDLK_k:
							s[max]='k';
							max++;
							break;
						case SDLK_l:
							s[max]='l';
							max++;
							break;
						case SDLK_m:
							s[max]='m';
							max++;
							break;
						case SDLK_n:
							s[max]='n';
							max++;
							break;
						case SDLK_o:
							s[max]='o';
							max++;
							break;
						case SDLK_p:
							s[max]='p';
							max++;
							break;
						case SDLK_q:
							s[max]='q';
							max++;
							break;
						case SDLK_r:
							s[max]='r';
							max++;
							break;
						case SDLK_s:
							s[max]='s';
							max++;
							break;
						case SDLK_t:
							s[max]='t';
							max++;
							break;
						case SDLK_u:
							s[max]='u';
							max++;
							break;
						case SDLK_v:
							s[max]='v';
							max++;
							break;
						case SDLK_w:
							s[max]='w';
							max++;
							break;
						case SDLK_x:
							s[max]='x';
							max++;
							break;
						case SDLK_y:
							s[max]='y';
							max++;
							break;
						case SDLK_z:
							s[max]='z';
							max++;
							break;
					}
					break;
			}					
		}
	}
	s[max]='\0';
	strcpy((*ptv).nom,s);
	(*ptv).score =score;
}

void affScore(joueur tab[], int n){
	if (n==100000){
		printf("Aucun joueur n'est enregistr\202.\n");
	}
	else{
		for(int z=0;z<n;z++){
			printf("%s : %d\n",tab[z].nom,tab[z].score);
		}
        }
}

SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y){
	SDL_Color color;
	Uint32 col=0;
	char *pPosition=(char*) pSurface->pixels;
	pPosition+=(pSurface->pitch *y);
	pPosition+=(pSurface->format->BytesPerPixel *x);
	memcpy(&col, pPosition ,pSurface->format->BytesPerPixel);
	SDL_GetRGB(col,pSurface->format,&color.r,&color.g,&color.b);
	return (color);
}


int CollitionParfaitePerso(SDL_Surface *MaskSurface,Personne perso){
	int a =0;
	a+=CollitionParfaite(MaskSurface,perso.position.x,perso.position.y+25-20);
	a+=CollitionParfaite(MaskSurface,perso.position.x+25,perso.position.y-18);
	a+=CollitionParfaite(MaskSurface,perso.position.x+25,perso.position.y+50-22);
	a+=CollitionParfaite(MaskSurface,perso.position.x+50,perso.position.y+5);

	a+=CollitionParfaite(MaskSurface,perso.position.x,perso.position.y-18);
	a+=CollitionParfaite(MaskSurface,perso.position.x,perso.position.y+50-22);
	a+=CollitionParfaite(MaskSurface,perso.position.x+50,perso.position.y+50-22);
	a+=CollitionParfaite(MaskSurface,perso.position.x+50,perso.position.y-18);

	a+=CollitionParfaite(MaskSurface,perso.position.x+12,perso.position.y-18);
	a+=CollitionParfaite(MaskSurface,perso.position.x+12,perso.position.y+50-22);
	a+=CollitionParfaite(MaskSurface,perso.position.x+38,perso.position.y+50-22);
	a+=CollitionParfaite(MaskSurface,perso.position.x+38,perso.position.y-18);

	a+=CollitionParfaite(MaskSurface,perso.position.x,perso.position.y-7);
	a+=CollitionParfaite(MaskSurface,perso.position.x,perso.position.y+17);
	a+=CollitionParfaite(MaskSurface,perso.position.x+50,perso.position.y+17);
	a+=CollitionParfaite(MaskSurface,perso.position.x+50,perso.position.y-7);

	return a;
}

int CollitionParfaitePersoB(SDL_Surface *MaskSurface,Personne perso){
	int a =0;
	a+=CollitionParfaiteB(MaskSurface,perso.position.x,perso.position.y+25-20);
	a+=CollitionParfaiteB(MaskSurface,perso.position.x+25,perso.position.y-18);
	a+=CollitionParfaiteB(MaskSurface,perso.position.x+25,perso.position.y+50-22);
	a+=CollitionParfaiteB(MaskSurface,perso.position.x+50,perso.position.y+5);

	a+=CollitionParfaiteB(MaskSurface,perso.position.x,perso.position.y-18);
	a+=CollitionParfaiteB(MaskSurface,perso.position.x,perso.position.y+50-22);
	a+=CollitionParfaiteB(MaskSurface,perso.position.x+50,perso.position.y+50-22);
	a+=CollitionParfaiteB(MaskSurface,perso.position.x+50,perso.position.y-18);

	a+=CollitionParfaiteB(MaskSurface,perso.position.x+12,perso.position.y-18);
	a+=CollitionParfaiteB(MaskSurface,perso.position.x+12,perso.position.y+50-22);
	a+=CollitionParfaiteB(MaskSurface,perso.position.x+38,perso.position.y+50-22);
	a+=CollitionParfaiteB(MaskSurface,perso.position.x+38,perso.position.y-18);

	a+=CollitionParfaiteB(MaskSurface,perso.position.x,perso.position.y-7);
	a+=CollitionParfaiteB(MaskSurface,perso.position.x,perso.position.y+17);
	a+=CollitionParfaiteB(MaskSurface,perso.position.x+50,perso.position.y+17);
	a+=CollitionParfaiteB(MaskSurface,perso.position.x+50,perso.position.y-7);

	return a;
}

int check_turn(Personne *Joueur,int ch_dir,int *dir,SDL_Surface *MaskSurface){
	deplacerPerso(Joueur, 4,ch_dir);
	if (CollitionParfaitePerso(MaskSurface,*Joueur)!=0){
		deplacerPerso(Joueur, 4,opp_dir(ch_dir));
	}
	else{
		(*dir)=ch_dir;
		return 1;
	}
	for(int i=0;i<3;i++){
		deplacerPerso(Joueur, 1,*dir);
		deplacerPerso(Joueur, 1,ch_dir);
		if (CollitionParfaitePerso(MaskSurface,*Joueur)!=0){
			deplacerPerso(Joueur, 1,opp_dir(ch_dir));
		}
		else{
			(*dir)=ch_dir;
			return 1;
		}
	}
	deplacerPerso(Joueur, 3,opp_dir(*dir));
	return 0;
}

int CollitionParfaite(SDL_Surface *MaskSurface,int x,int y){
	SDL_Color c;
	c=GetPixel(MaskSurface,x,y);
	if (c.r== 0 && c.g== 0 && c.b== 0){
		return 1;
	}
	return 0;
}

int CollitionParfaiteB(SDL_Surface *MaskSurface,int x,int y){
	SDL_Color c;
	c=GetPixel(MaskSurface,x,y);
	if (c.r== 255 && c.g== 255 && c.b== 255){
		return 1;
	}
	return 0;
}

void add_101(int* N){
	if (*N==1){
		(*N)=-1;
	}
	else{
		(*N)++;
	}
}

int opp_dir(int N){
	if (N==1){
		return 2;
	}
	else if (N==2){
		return 1;
	}
	else if (N==3){
		return 4;
	}
	else {
		return 3;
	}
}

int rand4(int a){
	int b=a;
	while(b==a){
		b=rand()%4+1;
	}
	return b;
}

void dim_101(int* N){
	if (*N==-1){
		(*N)=1;
	}
	else{
		(*N)--;
	}
}


void delay(int number_of_seconds){
	int milli_seconds = number_of_seconds,a;
	milli_seconds=milli_seconds*100000;
	clock_t start_time = clock();
	while (clock() < start_time + milli_seconds){
		a++;
	}
}

int check_descri(SDL_Event event,int x,int y,int w,int h){
	if(event.motion.x>=x && event.motion.x<=x+w && event.motion.y>=y && event.motion.y<=y+h){
		return 1;
	}
	else{
		return 0;
	}
}

void load_descri(Image* A,Image* B){
	(*A).img=IMG_Load("fondComDOUZs.png");
	(*B).img=IMG_Load("fondComMIDESs.png");
}

void aff_descri(SDL_Event event,Image A,Image B,SDL_Surface* ecran){
	SDL_Rect pos;
	if(check_descri(event,156,158,474,90)==1){
		pos.x=event.motion.x+10;
		pos.y=event.motion.y+10;
		SDL_BlitSurface(A.img,NULL,ecran,&pos);
	}
	else if(check_descri(event,150,880,480,160)==1){
		pos.x=event.motion.x-10;
		pos.y=event.motion.y-210;
		SDL_BlitSurface(B.img,NULL,ecran,&pos);
	}
}

void loadBouton(Bouton *B){
	(*B).etat=0;
	(*B).app.position.w=400;
	(*B).app.position.h=120;
	(*B).app.position.x=590;
	(*B).N_app.position.w=400;
	(*B).N_app.position.h=120;
	(*B).N_app.position.x=590;
}

void loadBoutonOP(Bouton *B,Bouton *B2){
	(*B).N_app.img=IMG_Load("vol_N.png");
	(*B).app.img=IMG_Load("vol_.png");
	(*B).etat=0;
	(*B).app.position.x=490;
	(*B).app.position.y=290;
	(*B).N_app.position.x=490;
	(*B).N_app.position.y=290;
	(*B).app.position.w=99;
	(*B).app.position.h=96;
	(*B).N_app.position.w=99;
	(*B).N_app.position.h=96;
	(*B2).N_app.img=IMG_Load("vol+N.png");
	(*B2).app.img=IMG_Load("vol+.png");
	(*B2).etat=0;
	(*B2).app.position.x=1050;
	(*B2).app.position.y=290;
	(*B2).N_app.position.x=1050;
	(*B2).N_app.position.y=290;
	(*B2).app.position.w=99;
	(*B2).app.position.h=96;
	(*B2).N_app.position.w=99;
	(*B2).N_app.position.h=96;
}

void load_allB(Bouton* J,Bouton* O,Bouton* Q){
	loadBouton(J);
	loadBouton(O);
	loadBouton(Q);
	
	(*J).N_app.img=IMG_Load("protoJ_Napp.png");
	(*J).app.img=IMG_Load("protoJ_app.png");
	
	(*O).N_app.img=IMG_Load("protoO_Napp.png");
	(*O).app.img=IMG_Load("protoO_app.png");

	(*Q).N_app.img=IMG_Load("protoQ_Napp.png");
	(*Q).app.img=IMG_Load("protoQ_app.png");

	(*J).app.position.y=440;
	(*O).app.position.y=600;
	(*Q).app.position.y=760;
	(*J).N_app.position.y=440;
	(*O).N_app.position.y=600;
	(*Q).N_app.position.y=760;
}

void Init_fond(Image *I){
	(*I).img=IMG_Load("j2.png");
	(*I).position.x=0;
	(*I).position.y=0;
}

void Init_Transi(Image *I,Image *P){
	(*I).img=IMG_Load("transiH.png");
	(*I).position.x=0;
	(*I).position.y=0;
	(*I).zone.x=0;
	(*I).zone.y=660;
	(*I).zone.w=1680;
	(*I).zone.h=0;
	(*P).img=IMG_Load("transiB.png");
	(*P).position.x=0;
	(*P).position.y=987;
}

void Aff_Transi(Image *I,Image *P,SDL_Surface* ecran,Image fond,Image Titre,SDL_Surface * LOGO[50],SDL_Surface *Text,Image zozor,Bouton Jouer,Bouton Option,Bouton Quitter,Image logo,SDL_Rect postxt,Selection select){
	while((*P).position.y>350){
		SDL_BlitSurface(fond.img,NULL,ecran,&fond.position);
		SDL_BlitSurface(Titre.img,NULL,ecran,&Titre.position);
		SDL_BlitSurface(LOGO[0],&logo.zone,ecran,&logo.position);
		SDL_BlitSurface(Text,NULL,ecran, &postxt);
		afficheFond(ecran, zozor,&(zozor.position.y));
		afficher_allBMENU(Jouer,Option,Quitter,ecran,select);
		SDL_BlitSurface((*I).img,&(*I).zone,ecran,&(*I).position);
		SDL_BlitSurface((*P).img,NULL,ecran,&(*P).position);
		(*P).position.y-=15;
		(*I).zone.y-=15;
		(*I).zone.h+=15;
		SDL_Flip(ecran);
	}
	delay(1);
}

void Aff_Transi_F_O(Image *I,Image *U,SDL_Surface* ecran,Image fond,Image Panneau,Image barre,Bouton D,Bouton A,Bouton R,Bouton F,Bouton P,Volume* V,Bouton M){
	while((*U).position.y!=987){
		SDL_BlitSurface(fond.img,NULL,ecran,&fond.position);
		SDL_BlitSurface(Panneau.img,NULL,ecran,&Panneau.position);
		SDL_BlitSurface(barre.img,NULL,ecran,&barre.position);
		afficher_allBO(D,A,ecran);
		afficherV((*V),ecran);
		afficherB(M,ecran);
		afficher_allB(R,F,P,ecran);
		SDL_BlitSurface((*I).img,&(*I).zone,ecran,&(*I).position);
		SDL_BlitSurface((*U).img,NULL,ecran,&(*U).position);
		(*U).position.y+=15;
		(*I).zone.y+=15;
		(*I).zone.h-=15;
		SDL_Flip(ecran);
	}
}

void Aff_Transi_F_J(Image *I,Image *U,SDL_Surface* ecran,Image jouerB, Bouton R,Image panneauJ, Bouton N1, Bouton N2, Bouton N3){
	while((*U).position.y!=987){
		SDL_BlitSurface(jouerB.img,NULL,ecran,&jouerB.position);
		SDL_BlitSurface(panneauJ.img,NULL,ecran,&panneauJ.position);
		afficherB(R,ecran);
		afficher_allB(N1,N2,N3,ecran);
		SDL_BlitSurface((*I).img,&(*I).zone,ecran,&(*I).position);
		SDL_BlitSurface((*U).img,NULL,ecran,&(*U).position);
		(*U).position.y+=15;
		(*I).zone.y+=15;
		(*I).zone.h-=15;
		SDL_Flip(ecran);
	}
}

void load_logoA(SDL_Surface * l[50]){
	char S[2],p[4],t[7];
	int k;
	for(int i=0;i<50;i++){
		k=i+1;
		sprintf(S,"%d",k);
		t[0]=S[0];
		t[1]=S[1];
		if(i>9){
			t[2]='.';
			t[3]='p';
			t[4]='n';
			t[5]='g';
			t[6]='\0';
		}
		else{
			t[1]='.';
			t[2]='p';
			t[3]='n';
			t[4]='g';
			t[5]='\0';
		}
		l[i]=IMG_Load(t);
	}
}

void afficherB(Bouton B,SDL_Surface* ecran){
	if(B.etat==0){
		SDL_BlitSurface(B.N_app.img,NULL,ecran,&B.N_app.position);
	}
	else {
		SDL_BlitSurface(B.app.img,NULL,ecran,&B.app.position);
	}
}

void afficher_allB(Bouton J,Bouton O,Bouton Q,SDL_Surface* ecran){
	afficherB(J,ecran);
	afficherB(O,ecran);
	afficherB(Q,ecran);
}

void afficherBMENU(Bouton B,SDL_Surface* ecran,Selection select,int a){
	if(select.S==0){
		if(B.etat==0){
			SDL_BlitSurface(B.N_app.img,NULL,ecran,&B.N_app.position);
		}
		else {
			SDL_BlitSurface(B.app.img,NULL,ecran,&B.app.position);
		}
	}
	else if (a==0){
		SDL_BlitSurface(B.N_app.img,NULL,ecran,&B.N_app.position);
	}
	else{
		SDL_BlitSurface(B.app.img,NULL,ecran,&B.app.position);
	}
}

void afficher_allBMENU(Bouton J,Bouton O,Bouton Q,SDL_Surface* ecran,Selection select){
	if (select.B==-1){
		afficherBMENU(J,ecran,select,1);
		afficherBMENU(O,ecran,select,0);
		afficherBMENU(Q,ecran,select,0);
	}
	else if (select.B==0){
		afficherBMENU(J,ecran,select,0);
		afficherBMENU(O,ecran,select,1);
		afficherBMENU(Q,ecran,select,0);
	}
	else{
		afficherBMENU(J,ecran,select,0);
		afficherBMENU(O,ecran,select,0);
		afficherBMENU(Q,ecran,select,1);
	}
}

void afficher_allBO(Bouton J,Bouton O,SDL_Surface* ecran){
	afficherB(J,ecran);
	afficherB(O,ecran);
}

int checkB(Bouton* B,SDL_Event event){
	int a=0;
	if(event.motion.x>=(*B).app.position.x && event.motion.x<=(*B).app.position.x+(*B).app.position.w && event.motion.y>=(*B).N_app.position.y && event.motion.y<=(*B).N_app.position.y+(*B).N_app.position.h){
		if ((*B).etat==0){
			a=1;
		}
		(*B).etat=1;
	}
	else{
		(*B).etat=0;
	}
	return a;
}

void flipB(Bouton* B,SDL_Event event,Mix_Chunk *son,int *sb){
	if(event.motion.x>=(*B).app.position.x && event.motion.x<=(*B).app.position.x+(*B).app.position.w && event.motion.y>=(*B).N_app.position.y && event.motion.y<=(*B).N_app.position.y+(*B).N_app.position.h){
		if ((*B).etat==1){
			Mix_VolumeChunk(son,MIX_MAX_VOLUME);
			(*sb)--;
			(*B).etat=0;
		}
		else{
			Mix_VolumeChunk(son,0);
			(*sb)++;
			(*B).etat=1;
		}
	}
}

int checkB_all(Bouton* J,Bouton* O,Bouton* Q,SDL_Event event){
	int ret=0;
	if(checkB(J,event)==1){
		ret++;
	}
	if(checkB(O,event)==1){
		ret++;
	}
	if(checkB(Q,event)==1){
		ret++;
	}
	return ret;
}

void Init_vol(Volume *B){
	(*B).app.img=IMG_Load("BoutonV2.png");
	(*B).app.position.x=636;
	(*B).app.position.y=311;
	(*B).vol=5;
}

void afficherV(Volume B,SDL_Surface* ecran){
	for (int i =0;i<B.vol;i++){
		SDL_BlitSurface(B.app.img,NULL,ecran,&B.app.position);
		B.app.position.x+=75;
	}
}

int checkB_allOP(Bouton* J,Bouton* O,SDL_Event event){
	int ret=0;
	if(checkB(J,event)==1){
		ret++;
	}
	if(checkB(O,event)==1){
		ret++;
	}
	return ret;
}

void mute(Bouton* B,SDL_Event event,Volume* V){
	if(event.motion.x>=(*B).app.position.x && event.motion.x<=(*B).app.position.x+(*B).app.position.w && event.motion.y>=(*B).N_app.position.y && event.motion.y<=(*B).N_app.position.y+(*B).N_app.position.h){
		if ((*B).etat==0){
			(*B).etat=1;
			(*V).vol=0;
		}
		else {
			(*B).etat=0;
			(*V).vol=5;
		}
	}
	else if((*V).vol==0){
		(*B).etat=1;
	}
	else if((*V).vol!=0){
		(*B).etat=0;
	}
}

int plein(Bouton* B,SDL_Event event,Uint32 flags){
	if(event.motion.x>=(*B).app.position.x && event.motion.x<=(*B).app.position.x+(*B).app.position.w && event.motion.y>=(*B).N_app.position.y && event.motion.y<=(*B).N_app.position.y+(*B).N_app.position.h){
		if ((*B).etat==0){
			(*B).etat=1;
			switchFullScreen(flags);
			return 1;
		}
		else {
			(*B).etat=0;
			SDL_SetVideoMode(0, 0, 0, flags^SDL_FULLSCREEN);
			return -1;
		}
	}
	return 0;
}

void option(SDL_Surface* ecran, Image fond,Uint32 flags,Volume* V,int *pl,Image* T_h,Image* T_b,int *sb,Mix_Chunk *son){
	int opt=1;
	SDL_Event evento;
	Bouton A,D,R,F,P,M;
	R.N_app.img=IMG_Load("R_Napp.png");
	R.app.img=IMG_Load("R_app.png");
	loadBouton(&R);
	R.N_app.position.y=710;
	R.app.position.y=710;
	R.N_app.position.x=630;
	R.app.position.x=630;
	F.N_app.img=IMG_Load("unmute1.png");
	F.app.img=IMG_Load("mute2.png");
	loadBouton(&F);
	if ((*V).vol==0){
		F.etat=1;
	}
	F.N_app.position.y=430;
	F.app.position.y=430;
	F.N_app.position.x=620;
	F.app.position.x=620;
	F.N_app.position.h=96;
	F.app.position.h=96;
	F.N_app.position.w=99;
	F.app.position.w=99;
	M.N_app.position.y=430;
	M.N_app.position.x=920;
	M.N_app.position.h=96;
	M.N_app.position.w=99;
	M.app.position.y=430;
	M.app.position.x=920;
	M.app.position.h=96;
	M.app.position.w=99;
	P.N_app.img=IMG_Load("P_E0.png");
	P.app.img=IMG_Load("p_E1.png");
	M.N_app.img=IMG_Load("SB.png");
	M.app.img=IMG_Load("SB_N2.png");
	if ((*pl)==1){
		P.etat=1;
	}
	else{
		P.etat=0;
	}
	if ((*sb)==1){
		M.etat=1;
	}
	else{
		M.etat=0;
	}
	P.N_app.position.y=570;
	P.app.position.y=570;
	P.N_app.position.x=770;
	P.app.position.x=770;
	P.N_app.position.h=96;
	P.app.position.h=96;
	P.N_app.position.w=99;
	P.app.position.w=99;
	
	loadBoutonOP(&D,&A);
	Image barre,Panneau;
	Panneau.img=IMG_Load("F_option2.png");
	barre.img=IMG_Load("barre_vol3.png");
	Panneau.position.x=0;
	Panneau.position.y=0;
	barre.position.x=624;
	barre.position.y=290;
	Aff_Transi_F_O(T_h,T_b,ecran,fond,Panneau,barre,D,A,R,F,P,V,M);
	while(opt){
		int y=0;
		Mix_VolumeMusic(((*V).vol)*(MIX_MAX_VOLUME/5));
		SDL_BlitSurface(fond.img,NULL,ecran,&fond.position);
		SDL_BlitSurface(Panneau.img,NULL,ecran,&Panneau.position);
		SDL_BlitSurface(barre.img,NULL,ecran,&barre.position);
		afficher_allBO(D,A,ecran);
		afficherV((*V),ecran);
		afficher_allB(R,F,P,ecran);
		afficherB(M,ecran);
		SDL_Flip(ecran);
		while(SDL_PollEvent(&evento)){
			switch(evento.type){
				case SDL_QUIT:
					opt=0;
					break;
				case SDL_MOUSEMOTION:
					checkB_allOP(&D,&A,evento);
					checkB(&R,evento);
					break;
				case SDL_MOUSEBUTTONDOWN:
					flipB(&M,evento,son,sb);
					if(D.etat == 1){
						if((*V).vol>0){
							(*V).vol--;
						}
					}
					else if(A.etat == 1){
						if((*V).vol<5){
							(*V).vol++;
						}
					}
					else if(R.etat == 1){
						opt=0;
					}
					mute(&F,evento,V);
					y=plein(&P,evento,flags);
					if (y==1){
						SDL_WarpMouse(800,600);
						(*pl)=1;
					}
					else if (y==-1) {
						SDL_WarpMouse(800,600);
						(*pl)=0;
					}
					break;
				case SDL_KEYDOWN:
					switch(evento.key.keysym.sym){
						case SDLK_ESCAPE:
							opt =0;
							break;
						case SDLK_r:
							opt =0;
							break;
					}
					break;
			}					
		}
	}
}

void init_niv1(Personne *Joueur,Personne *mechant,Personne *mechant1,Personne *mechant2,Personne *mechant3){
	(*Joueur).vies=3;
	(*mechant).position.x=782;
	(*mechant).position.y=445;
	(*mechant).position.w=50;
	(*mechant).position.h=50;
	(*mechant).initial=IMG_Load("mechan.png");
	(*mechant).vies=0;
	(*mechant).etat=0;
	(*mechant1).position.x=782;
	(*mechant1).position.y=445;
	(*mechant1).position.w=50;
	(*mechant1).position.h=50;
	(*mechant1).initial=IMG_Load("mechan.png");
	(*mechant1).vies=0;
	(*mechant1).etat=0;
	(*mechant2).position.x=782;
	(*mechant2).position.y=445;
	(*mechant2).position.w=50;
	(*mechant2).position.h=50;
	(*mechant2).initial=IMG_Load("mechan.png");
	(*mechant2).vies=0;
	(*mechant2).etat=0;
	(*mechant3).position.x=782;
	(*mechant3).position.y=445;
	(*mechant3).position.w=50;
	(*mechant3).position.h=50;
	(*mechant3).initial=IMG_Load("mechan.png");
	(*mechant3).vies=0;
	(*mechant3).etat=0;
	initPerso(Joueur);
}

void sortir(time_t start,Personne *mechant,Personne *mechant1,Personne *mechant2,Personne *mechant3){
	time_t end = time( NULL);
    	unsigned long secondes = (unsigned long) difftime( end, start );
   	int sec = (int) secondes;
	if (sec>0){
		if((*mechant).vies!=1){
			(*mechant).vies=2;
		}
		if (((*mechant).vies==2)&&((*mechant).position.x<790)){
			(*mechant).position.x+=4;
			if ((*mechant).position.x>790){
				(*mechant).position.x=790;
			}
		}
		else if (((*mechant).vies==2)&&((*mechant).position.x>790)){
			(*mechant).position.x-=4;
			if ((*mechant).position.x<790){
				(*mechant).position.x=790;
			}
		}
		else if (((*mechant).vies==2)&&((*mechant).position.x==790)){
			(*mechant).position.y-=4;
			if ((*mechant).position.y<370){
				(*mechant).position.y=370;
				(*mechant).vies=1;
			}
		}
	}
	if (sec>15){
		if((*mechant1).vies!=1){
			(*mechant1).vies=2;
		}
		if (((*mechant1).vies==2)&&((*mechant1).position.x<790)){
			(*mechant1).position.x+=4;
			if ((*mechant1).position.x>790){
				(*mechant1).position.x=790;
			}
		}
		else if (((*mechant1).vies==2)&&((*mechant1).position.x>790)){
			(*mechant1).position.x-=4;
			if ((*mechant1).position.x<790){
				(*mechant1).position.x=790;
			}
		}
		else if (((*mechant1).vies==2)&&((*mechant1).position.x==790)){
			(*mechant1).position.y-=4;
			if ((*mechant1).position.y<370){
				(*mechant1).position.y=370;
				(*mechant1).vies=1;
			}
		}
	}
	if (sec>30){
		if((*mechant2).vies!=1){
			(*mechant2).vies=2;
		}
		if (((*mechant2).vies==2)&&((*mechant2).position.x<790)){
			(*mechant2).position.x+=4;
			if ((*mechant2).position.x>790){
				(*mechant2).position.x=790;
			}
		}
		else if (((*mechant2).vies==2)&&((*mechant2).position.x>790)){
			(*mechant2).position.x-=4;
			if ((*mechant2).position.x<790){
				(*mechant2).position.x=790;
			}
		}
		else if (((*mechant2).vies==2)&&((*mechant2).position.x==790)){
			(*mechant2).position.y-=4;
			if ((*mechant2).position.y<370){
				(*mechant2).position.y=370;
				(*mechant2).vies=1;
			}
		}
	}
	if (sec>40){
		if((*mechant3).vies!=1){
			(*mechant3).vies=2;
		}
		if (((*mechant3).vies==2)&&((*mechant3).position.x<790)){
			(*mechant3).position.x+=4;
			if ((*mechant3).position.x>790){
				(*mechant3).position.x=790;
			}
		}
		else if (((*mechant3).vies==2)&&((*mechant3).position.x>790)){
			(*mechant3).position.x-=4;
			if ((*mechant3).position.x<790){
				(*mechant3).position.x=790;
			}
		}
		else if (((*mechant3).vies==2)&&((*mechant3).position.x==790)){
			(*mechant3).position.y-=4;
			if ((*mechant3).position.y<370){
				(*mechant3).position.y=370;
				(*mechant3).vies=1;
			}
		}
	}
}

void teleporte(Personne *P,int *dir){
	if ((*P).position.x>1415 && (*P).position.y==473 && (*dir)!=2){
		(*P).position.x=94;
		(*dir)=1;
	}
	else if((*P).position.x<96 && (*P).position.y==473 && (*dir)!=1){
		(*P).position.x=1417;
		(*dir)=2;
	}
}

void remplir(int tab[2][18]){
	tab[0][0]=167;
	tab[0][1]=233;
	tab[0][2]=302;
	tab[0][3]=376;
	tab[0][4]=447;
	tab[0][5]=513;
	tab[0][6]=584;
	tab[0][7]=652;
	tab[0][8]=725;
	tab[0][9]=792;
	tab[0][10]=864;
	tab[0][11]=934;
	tab[0][12]=1003;
	tab[0][13]=1077;
	tab[0][14]=1142;
	tab[0][15]=1217;
	tab[0][16]=1282;
	tab[0][17]=1353;

	tab[1][0]=161;
	tab[1][1]=229;
	tab[1][2]=299;
	tab[1][3]=370;
	tab[1][4]=440;
	tab[1][5]=510;
	tab[1][6]=577;
	tab[1][7]=648;
	tab[1][8]=719;
	tab[1][9]=791;	
}

int verifier_vict(Objniv1 O){
	for(int i=0;i<18;i++){
		for(int j=0;j<10;j++){
			if ((O).tab[i][j].etat==1){
				return 0;
			}
		}
	}
	return 1;
}

void init_obj(Objniv1 * O){
	int tableau[2][18];
	remplir(tableau);
	(*O).img=IMG_Load("weapon2_1.png");
	(*O).bombe=IMG_Load("weapon1_1.png");
	int x=167,y=161;
	for(int i=0;i<18;i++){
		for(int j=0;j<10;j++){
			(*O).tab[i][j].etat=1;
			(*O).tab[i][j].position.x=tableau[0][i];
			(*O).tab[i][j].position.y=tableau[1][j];
			if(i==12 && j==0){
				(*O).tab[i][j].etat=0;
			}
			else if(i==11 && j==8){
				(*O).tab[i][j].etat=0;
			}
			else if((i>6) && (i<11) && (j>3) && (j<6)){
				(*O).tab[i][j].etat=0;
			}
		}
	}
}

void aff_obj(Objniv1 O,SDL_Surface *ecran){
	for(int i=0;i<18;i++){
		for(int j=0;j<10;j++){
			if(O.tab[i][j].etat==1){
				if (i==4 && j==1){
					SDL_BlitSurface(O.bombe, NULL, ecran, &O.tab[i][j].position);
				}
				else if (i==7 && j==9){
					SDL_BlitSurface(O.bombe, NULL, ecran, &O.tab[i][j].position);
				}
				else if (i==16 && j==4){
					SDL_BlitSurface(O.bombe, NULL, ecran, &O.tab[i][j].position);
				}
				else{
					SDL_BlitSurface(O.img, NULL, ecran, &O.tab[i][j].position);
				}
			}
		}
	}
}

void aff_pilier(Objet t[40],SDL_Surface *img,SDL_Surface *ecran){
	for(int i=0;i<40;i++){
		if(t[i].etat==1){
			SDL_BlitSurface(img, &t[i].zone, ecran,&t[i].position);
		}
	}
}

void mv_pilier(Objet *p,int *d){
	if((*p).position.x==1200 && (*d)==1){
		(*d)=-1;
	}
	else if((*p).position.x==264 && (*d)==-1){
		(*d)=1;
	}
	else{ 
		(*p).position.x=(*p).position.x+(*d)*8;
	}
}

void tmb_pilier(Objet *p,int *d){
	if((*p).position.x>=1200 && (*d)==1){
		(*p).position.x=1200;
		(*d)=-1;
	}
	else if((*p).position.x<=264 && (*d)==-1){
		(*d)=1;
		(*p).position.x=264;
	}
	
	if((*p).position.y<200){
		(*p).position.y=(*p).position.y+4;
		(*p).position.x=(*p).position.x+(*d)*6;
	}
	else if((*p).position.y<400){
		(*p).position.y=(*p).position.y+8;
		(*p).position.x=(*p).position.x+(*d)*4;
	}
	else if((*p).position.y<590){
		(*p).position.y=(*p).position.y+16;
		(*p).position.x=(*p).position.x+(*d)*2;
	}
	if((*p).position.y>590){
		(*p).position.y=590;
	}
}

void manger(Objniv1 * O,Personne *P,int *a,time_t *start){
	float k,f,s;
	for(int i=0;i<18;i++){
		for(int j=0;j<10;j++){
			f=carre((*O).tab[i][j].position.x+25-((*P).position.x+20));
			s=carre((*O).tab[i][j].position.y+25-((*P).position.y+20));
			k= racine(f+s);
			if(k<25){
				if (i==4 && j==1 && (*O).tab[i][j].etat!=0){
					(*a)=1;
					*start = time( NULL);
					(*O).tab[i][j].etat=0;
					(*P).initial=IMG_Load("tueur.png");
				}
				else if (i==7 && j==9 && (*O).tab[i][j].etat!=0){
					(*a)=1;
					*start = time( NULL);
					(*O).tab[i][j].etat=0;
					(*P).initial=IMG_Load("tueur.png");
				}
				else if (i==16 && j==4 && (*O).tab[i][j].etat!=0){
					(*a)=1;
					*start = time( NULL);
					(*O).tab[i][j].etat=0;
					(*P).initial=IMG_Load("tueur.png");
				}
				else{
					(*O).tab[i][j].etat=0;
				}
			}
		}
	}
}

void check_tuer(int *a,time_t *start,Personne *P){
	time_t now = time( NULL);
	unsigned long secondes = (unsigned long) difftime( now, *start );
	int sec = (int) secondes;
	if (sec>10){
		(*a)=0;
		(*P).initial=IMG_Load("personiv.png");
	}
}

void afficher_(SDL_Surface * screen,int score,int vies){
	SDL_Surface *Text=NULL;
	SDL_Rect postxt;
	int length = snprintf( NULL, 0, "Score : %d",score);
	char* str = malloc( length + 1 );
	snprintf( str, length + 1, "Score : %d",score);
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


void jouer(SDL_Surface *ecran, Image jouerB,Image* T_h,Image* T_b,int score,joueur tab[], int * n){
	int jj=1;
	Bouton R,N1,N2,N3;
	Image panneauJ,cdr,buche,pierre,lance,peau;
	Image ffff,cadre_niv2,bougar,ciel;
	ffff.img=IMG_Load("fond_niv_1.02.png");
	ffff.position.x=0;
	ffff.position.y=20;
	
	bougar.img=IMG_Load("back2.png");

	SDL_Surface *PL;
	PL=IMG_Load("pilier2.png");
	Objet TPL[40];

	lance.img=IMG_Load("lance.png");
	lance.position.x=1391;
	lance.position.y=105;

	pierre.img=IMG_Load("pierre.png");
	pierre.position.x=1386;
	pierre.position.y=113;

	buche.img=IMG_Load("buche.png");
	buche.position.x=1386;
	buche.position.y=170;

	peau.img=IMG_Load("peau.png");
	peau.position.x=1391;
	peau.position.y=170;

	cdr.img=IMG_Load("cadre_niv2.png");
	cdr.position.x=0;
	cdr.position.y=0;
	
	ciel.img=IMG_Load("cadre_niv2_c.png");
	ciel.position.x=0;
	ciel.position.y=0;

	cadre_niv2.img=IMG_Load("F2_cadre.png");
	cadre_niv2.position.x=0;
	cadre_niv2.position.y=0;

	Background Bm,Bg;
	Bm.img= IMG_Load("fond_niv3_masque.png");

	panneauJ.img=IMG_Load("panneauJ2.png");
	panneauJ.position.x=398;
	panneauJ.position.y=20;
	R.N_app.img=IMG_Load("R_Napp.png");
	R.app.img=IMG_Load("R_app.png");
	loadBouton(&R);
	R.N_app.position.y=710;
	R.app.position.y=710;
	R.N_app.position.x=570;
	R.app.position.x=570;



	loadBouton(&N1);
	loadBouton(&N2);
	loadBouton(&N3);
	N1.N_app.img=IMG_Load("bouton_indis.png");
	N2.N_app.img=IMG_Load("bouton_indis.png");
	N3.N_app.img=IMG_Load("bouton_indis.png");
	N1.app.img=IMG_Load("bouton_dis.png");
	N2.app.img=IMG_Load("bouton_dis.png");
	N3.app.img=IMG_Load("bouton_dis.png");
	
	N1.N_app.position.y=150;
	N1.app.position.y=150;
	N1.N_app.position.x=570;
	N1.app.position.x=570;
	
	N2.N_app.position.y=350;
	N2.app.position.y=350;
	N2.N_app.position.x=570;
	N2.app.position.x=570;
	
	N3.N_app.position.y=550;
	N3.app.position.y=550;
	N3.N_app.position.x=570;
	N3.app.position.x=570;


	SDL_Surface *MaskSurface;
	MaskSurface=IMG_Load("fond_niv_1.03.1.png");
	

	SDL_Event eventj,eventniv;
	Aff_Transi_F_J(T_h,T_b,ecran,jouerB,R,panneauJ,N1,N2,N3);
	while (jj){
		SDL_BlitSurface(jouerB.img,NULL,ecran,&jouerB.position);
		SDL_BlitSurface(panneauJ.img,NULL,ecran,&panneauJ.position);
		afficherB(R,ecran);
		afficher_allB(N1,N2,N3,ecran);
		SDL_Flip(ecran);
		while(SDL_PollEvent(&eventj)){
			switch(eventj.type){
				case SDL_QUIT:
					jj=0;
					break;
				case SDL_MOUSEMOTION:
					checkB(&R,eventj);
					checkB(&N1,eventj);
					checkB(&N2,eventj);
					checkB(&N3,eventj);
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(N1.etat == 1){
						time_t begin = time( NULL );
						time_t killer = time( NULL );
						int tuer=0,niv1=1,dir=2,dir2=2,dir3=2,dir4=2,dir5=2,ch_dir=2,ch_mech=2,ch_mech1=2,ch_mech2=2,ch_mech3=2,change=0,change2=0,change3=0,change4=0,change5=0;
						Personne Joueur,mechant,mechant1,mechant2,mechant3;
						Objniv1 Ob;
						init_niv1(&Joueur,&mechant,&mechant1,&mechant2,&mechant3);
						init_obj(&Ob);
						while (niv1 && Joueur.vies!=0 && !verifier_vict(Ob)){
							sortir(begin,&mechant,&mechant1,&mechant2,&mechant3);
							change=0;
							change2=0;
							teleporte(&Joueur,&dir);
							teleporte(&mechant,&dir2);
							teleporte(&mechant1,&dir3);
							teleporte(&mechant2,&dir4);
							teleporte(&mechant3,&dir5);
							SDL_BlitSurface(jouerB.img,NULL,ecran,&jouerB.position);
							SDL_BlitSurface(ffff.img,NULL,ecran,&ffff.position);
							aff_obj(Ob,ecran);
							afficherPerso(&Joueur,ecran);
							afficherPerso(&mechant,ecran);
							afficherPerso(&mechant1,ecran);
							afficherPerso(&mechant2,ecran);
							afficherPerso(&mechant3,ecran);
							SDL_Flip(ecran);
							manger(&Ob,&Joueur,&tuer,&killer);
							change=check_turn(&Joueur,ch_dir,&dir,MaskSurface);
							if (change==0){
								deplacerPerso(&Joueur, 4,dir);
								if (CollitionParfaitePerso(MaskSurface,Joueur)!=0){
									deplacerPerso(&Joueur, 4,opp_dir(dir));
								}
							}
							if(mechant.vies==1){
								if(rand()%100==2){
									ch_mech=rand4(dir2);						
								}
								change2=check_turn(&mechant,ch_mech,&dir2,MaskSurface);
								if (change2==0){
									deplacerPerso(&mechant, 4,dir2);
									if (CollitionParfaitePerso(MaskSurface,mechant)!=0){
										deplacerPerso(&mechant, 4,opp_dir(dir2));
										ch_mech=rand4(10);
									}
								}
							}
							else if(mechant.vies==0){
								deplacerPerso(&mechant, 4,dir2);
								if (CollitionParfaitePerso(MaskSurface,mechant)!=0){
									deplacerPerso(&mechant, 4,opp_dir(dir2));
									dir2=rand4(opp_dir(dir2));
								}
							}
							if(mechant1.vies==1){
								if(rand()%100==2){
									ch_mech1=rand4(dir3);						
								}
								change3=check_turn(&mechant1,ch_mech1,&dir3,MaskSurface);
								if (change3==0){
									deplacerPerso(&mechant1, 4,dir3);
									if (CollitionParfaitePerso(MaskSurface,mechant1)!=0){
										deplacerPerso(&mechant1, 4,opp_dir(dir3));
										ch_mech1=rand4(10);
									}
								}
							}
							else if(mechant1.vies==0){
								deplacerPerso(&mechant1, 4,dir3);
								if (CollitionParfaitePerso(MaskSurface,mechant1)!=0){
									deplacerPerso(&mechant1, 4,opp_dir(dir3));
									dir3=rand4(opp_dir(dir3));
								}
							}
							if(mechant2.vies==1){
								if(rand()%100==2){
									ch_mech2=rand4(dir4);						
								}
								change4=check_turn(&mechant2,ch_mech2,&dir4,MaskSurface);
								if (change4==0){
									deplacerPerso(&mechant2, 4,dir4);
									if (CollitionParfaitePerso(MaskSurface,mechant2)!=0){
										deplacerPerso(&mechant2, 4,opp_dir(dir4));
										ch_mech2=rand4(10);
									}
								}
							}
							else if(mechant2.vies==0){
								deplacerPerso(&mechant2, 4,dir4);
								if (CollitionParfaitePerso(MaskSurface,mechant2)!=0){
									deplacerPerso(&mechant2, 4,opp_dir(dir4));
									dir4=rand4(opp_dir(dir4));
								}
							}
							if(mechant3.vies==1){
								if(rand()%100==2){
									ch_mech3=rand4(dir5);						
								}
								change5=check_turn(&mechant3,ch_mech3,&dir5,MaskSurface);
								if (change5==0){
									deplacerPerso(&mechant3, 4,dir5);
									if (CollitionParfaitePerso(MaskSurface,mechant3)!=0){
										deplacerPerso(&mechant3, 4,opp_dir(dir5));
										ch_mech3=rand4(10);
									}
								}
							}
							else if(mechant3.vies==0){
								deplacerPerso(&mechant3, 4,dir5);
								if (CollitionParfaitePerso(MaskSurface,mechant3)!=0){
									deplacerPerso(&mechant3, 4,opp_dir(dir5));
									dir5=rand4(opp_dir(dir5));
								}
							}
							check_tuer(&tuer,&killer,&Joueur);
							if(collision(Joueur,mechant,mechant1,mechant2,mechant3)==1){
								if (tuer==0){
									delay(2);
									mort(&Joueur,&mechant,&mechant1,&mechant2,&mechant3,&begin);
								}
								else{
									if (collisionBB( Joueur, mechant)==1){
										delay(2);
										mort_E(&mechant,&begin);
									}
									else if(collisionBB( Joueur, mechant1)==1){
										delay(2);
										mort_E(&mechant1,&begin);
									}
									else if(collisionBB( Joueur, mechant2)==1){
										delay(2);
										mort_E(&mechant2,&begin);
									}
									else if(collisionBB( Joueur, mechant3)==1){
										delay(2);
										mort_E(&mechant3,&begin);
									}
								}
							}
							while(SDL_PollEvent(&eventniv)){
								switch(eventniv.type){
									case SDL_QUIT:
										niv1=0;
										break;
									case SDL_MOUSEMOTION:
										break;
									case SDL_KEYDOWN:
										switch(eventniv.key.keysym.sym){
											case SDLK_ESCAPE:
												niv1=0;
												break;
											case SDLK_RIGHT:
												ch_dir=1;
												break;
											case SDLK_LEFT:
												ch_dir=2;
												break;
											case SDLK_DOWN:
												ch_dir=3;
												break;
											case SDLK_UP:
												ch_dir=4;
												break;
										}
										break;
								}
							}
						}
						SDL_Surface *FIN;
						SDL_Rect finit;
						SDL_Event terminus;
						finit.x=0;
						finit.y=0;
						if (verifier_vict(Ob)==1){
							FIN =IMG_Load("win.png");
						}
						else{
							FIN =IMG_Load("lose.png");
						}
						int fin =1;
						while(fin){
							SDL_BlitSurface(FIN,NULL,ecran,&finit);
							SDL_Flip(ecran);
							while(SDL_PollEvent(&terminus)){
								switch(terminus.type){
									case SDL_QUIT:
										fin=0;
										break;
									case SDL_MOUSEMOTION:
										break;
									case SDL_MOUSEBUTTONDOWN:
										break;
									case SDL_KEYDOWN:
										switch(terminus.key.keysym.sym){
											case SDLK_ESCAPE:
											case SDLK_e:
												fin=0;
												break;
										}
										break;
								}					
							}
						}

					}
					else if(N3.etat == 1){
						minimap m;
						initminimap(&m);
						
						int niv2=1,r=0,l=0,d=0,u=0,life_cow=1,nb=0,nr=0,np=0;
						Personne Joueur;
						Joueur.vies=3;
						Image ar1,ar2,ar3,ar0,rk1,rk2,rk3,rk0,house,door,oiseau,cow;
						int T_R[6];
						for (int o=0;o<6;o++){
							T_R[o]=1;
						}
						initArb(&ar1,&ar2,&ar3,&ar0);
						initRock(&rk1,&rk2,&rk3,&rk0);
						initBack(&Bg);
						initanime(&oiseau,&cow);
						inithouse(&house,&door);
						initp(&Joueur);
						time_t begin2 = time( NULL );
						while (niv2 && Joueur.vies!=0){
							if(scrolling (&Joueur,r,l,d,u,Bm.img)==1){
								for(int an=0;an<5;an++){
									animedoor(&door);
									SDL_BlitSurface(jouerB.img,NULL,ecran,&jouerB.position);
									MAJMinimap(Joueur.position, &m);
									afficherBack(Bg,Joueur,ecran);
									afficher_all_Arb(ar1,ar2,ar3,ar0,Joueur, ecran,T_R);
									afficherArb(rk1,Joueur,ecran,T_R[3],rk0);
									afficherArb(rk2,Joueur,ecran,T_R[4],rk0);
									afficherArb(rk3,Joueur,ecran,T_R[5],rk0);
									afficher_im(house,Joueur, ecran);
									afficher_im(door,Joueur, ecran);
									affichercow(cow,Joueur,ecran,life_cow);
									animep(&Joueur,r,l,d,u);
									afficherp(Joueur,ecran);
									animerBackground(&oiseau);
									afficher_im(oiseau,Joueur, ecran);
									
									aff_inv(lance,pierre,buche,peau,ecran,nb,nr,np);
									SDL_BlitSurface(cadre_niv2.img,NULL,ecran,&cadre_niv2.position);
									afficherminimap (m,begin2,ecran,score,Joueur.vies);
							
									SDL_Flip(ecran);
									SDL_Delay(200);
								}
								SDL_Delay(800);
								enigmealea(ecran);
								SDL_Delay(2000);
								Joueur.position.x=7200;
								Joueur.position.y=5400;
							}
							
							if(collisionBB_niv3(Joueur,ar1)==1){
								T_R[0]=0;
							}
							if(collisionBB_niv3(Joueur,ar2)==1){
								T_R[1]=0;
							}
							if(collisionBB_niv3(Joueur,ar3)==1){
								T_R[2]=0;
							}
							if(collisionrocher(Joueur,rk1)==1){
								T_R[3]=0;
								rk1.img=IMG_Load("rock_B.png");
							}
							if(collisionrocher(Joueur,rk2)==1){
								T_R[4]=0;
								rk2.img=IMG_Load("rock_B.png");
							}
							if(collisionrocher(Joueur,rk3)==1){
								T_R[5]=0;
								rk3.img=IMG_Load("rock_B.png");
							}
							nb=3-(T_R[1]+T_R[0]+T_R[2]);
							nr=3-(T_R[5]+T_R[4]+T_R[3]);
							SDL_BlitSurface(jouerB.img,NULL,ecran,&jouerB.position);
							MAJMinimap(Joueur.position, &m);
							afficherBack(Bg,Joueur,ecran);
							afficher_all_Arb(ar1,ar2,ar3,ar0,Joueur, ecran,T_R);
							afficher_all_Arb(rk1,rk2,rk3,rk0,Joueur, ecran,T_R);
							afficher_im(house,Joueur, ecran);
							afficher_im(door,Joueur, ecran);
							deplacercow(&cow,Joueur);
							if(collisionrocher(Joueur,cow)==1){
								if (nb==3 && nr ==3){
									life_cow=0;
									np=1;
								}
								else{
									Joueur.vies--;
									Joueur.position.x=5500;
    									Joueur.position.y=2900;
								}
							}
							affichercow(cow,Joueur,ecran,life_cow);
							animep(&Joueur,r,l,d,u);
							afficherp(Joueur,ecran);
							animerBackground(&oiseau);
							afficher_im(oiseau,Joueur, ecran);
							
							aff_inv(lance,pierre,buche,peau,ecran,nb,nr,np);
							SDL_BlitSurface(cadre_niv2.img,NULL,ecran,&cadre_niv2.position);
							afficherminimap (m,begin2,ecran,score,Joueur.vies);
							
							SDL_Flip(ecran);

							while(SDL_PollEvent(&eventniv)){
								switch(eventniv.type){
									case SDL_QUIT:
										niv2=0;
										break;
									case SDL_MOUSEMOTION:
										break;
									case SDL_KEYDOWN:
										switch(eventniv.key.keysym.sym){
											case SDLK_ESCAPE:
												niv2=0;
												break;
											case SDLK_RIGHT:
												d=0;
												u=0;
												l=0;
												r=1;	
												break;
											case SDLK_LEFT:
												d=0;
												u=0;
												r=0;
												l=1;
												break;
											case SDLK_DOWN:
												u=0;
												l=0;
												r=0;
												d=1;
												break;
											case SDLK_UP:
												d=0;
												l=0;
												r=0;
												u=1;
												break;
										}
										break;
									case SDL_KEYUP:
										switch(eventniv.key.keysym.sym){
											case SDLK_ESCAPE:
												niv2=0;
												break;
											case SDLK_RIGHT:
												r=0;
												break;
											case SDLK_LEFT:
												l=0;
												break;
											case SDLK_UP:
												u=0;
												break;
											case SDLK_DOWN:
												d=0;
												break;
										}
										break;
								}
							}
						}
						joueur v;
						saisirJ (&v,score,ecran);
						ajouter (v,tab, n);
						affScore(tab,*n);
					}
					else if(N2.etat == 1){
						time_t begin3 = time( NULL );
						int niv3=1,pilier=0,direc=1,tombe=0,w=1,lose_2=0;
						Personne Joueur;
						for(int i=0;i<40;i++){
							TPL[i].etat=0;
							TPL[i].position.x=736;
							TPL[i].position.y=110;
							TPL[i].zone.y=0;
							TPL[i].zone.x=0;
							TPL[i].zone.h=150;
							TPL[i].zone.w=100;
						}
						bougar.position.x=0;
						bougar.position.y=0;
						bougar.zone.x=0;
						bougar.zone.y=0;
						bougar.zone.h=880;
						bougar.zone.w=1580;
						TPL[0].etat=1;
						SDL_Surface *Mess=NULL;
						SDL_Rect posmess;
						TTF_Font *polic=NULL;
						SDL_Color couleu={255, 191, 64};
						polic = TTF_OpenFont("REVISTA.ttf",60);
						Mess = TTF_RenderText_Blended(polic,"Press SPACE to Start",couleu);
						posmess.x=400;
						posmess.y=300;
						while (niv3 && pilier<40){
							if (tombe==1){
								tmb_pilier(&TPL[pilier],&direc);
								if (TPL[pilier].position.y==590){
									tombe=0;
									if (pilier>0 && (TPL[pilier-1].position.x>TPL[pilier].position.x+100 || TPL[pilier-1].position.x+100<TPL[pilier].position.x)){
										w=0;
										SDL_Surface *FIN;
										SDL_Rect finit;
										finit.x=0;
										finit.y=0;
										FIN =IMG_Load("lose.png");
										SDL_BlitSurface(FIN,NULL,ecran,&finit);
										SDL_Flip(ecran);
										delay(10);
										lose_2=1;
										niv3=0;
									}
									while(TPL[pilier].position.y!=740 && w){
										SDL_BlitSurface(jouerB.img,NULL,ecran,&jouerB.position);
										SDL_BlitSurface(ciel.img,NULL,ecran,&ciel.position);
										SDL_BlitSurface(bougar.img,&bougar.zone,ecran,&bougar.position);
										aff_pilier(TPL,PL,ecran);
										SDL_BlitSurface(cdr.img,NULL,ecran,&cdr.position);
										SDL_Flip(ecran);
										TPL[pilier].position.y+=5;
										if(TPL[pilier].position.y>730){
											TPL[pilier].zone.h-=5;
										}
										if(pilier>0){
											if(TPL[pilier-1].position.y>730 && TPL[pilier-1].zone.h>0){
												TPL[pilier-1].zone.h-=5;
												TPL[pilier-1].position.y+=5;
											}
										}
										if(bougar.zone.h>0){
											bougar.zone.h-=5;
											bougar.position.y+=5;
										}
									}
									pilier++;
									TPL[pilier].etat=1;
								}
							}
							SDL_BlitSurface(jouerB.img,NULL,ecran,&jouerB.position);
							SDL_BlitSurface(ciel.img,NULL,ecran,&ciel.position);
							SDL_BlitSurface(bougar.img,&bougar.zone,ecran,&bougar.position);
							aff_pilier(TPL,PL,ecran);
							SDL_BlitSurface(cdr.img,NULL,ecran,&cdr.position);
							if(tombe==0 && pilier == 0){
								SDL_BlitSurface(Mess,NULL,ecran, &posmess);
							}
							SDL_Flip(ecran);
							if (tombe==0){
								mv_pilier(&TPL[pilier],&direc);
							}
							while(SDL_PollEvent(&eventniv)){
								switch(eventniv.type){
									case SDL_QUIT:
										niv3=0;
										break;
									case SDL_MOUSEMOTION:
										break;
									case SDL_KEYDOWN:
										switch(eventniv.key.keysym.sym){
											case SDLK_SPACE:
												if (tombe==0){
													tombe=1;
												}
												break;
											case SDLK_ESCAPE:
												niv3=0;
												break;
											case SDLK_RIGHT:
												break;
											case SDLK_LEFT:
												break;
											case SDLK_DOWN:
												break;
											case SDLK_UP:
												break;
										}
										break;
								}
							}
							
						}
						if (!lose_2){
							SDL_Surface *FIN;
							SDL_Rect finit;
							finit.x=0;
							finit.y=0;
							FIN =IMG_Load("win.png");
							SDL_BlitSurface(FIN,NULL,ecran,&finit);
							SDL_Flip(ecran);
							delay(10);
						}
					}
					else if(R.etat == 1){
						jj=0;
					}
					break;
				case SDL_KEYDOWN:
					switch(eventj.key.keysym.sym){
						case SDLK_ESCAPE:
							jj=0;
							break;
						case SDLK_r:
							jj =0;
							break;
					}
					break;
			}
		}
	}
}

void afficheFond(SDL_Surface *ecran, Image zozor, Sint16* a){
	zozor.position.y += 10;
	if ( (*a) <50){
		(*a) = 50;
	}
	else if(zozor.position.y < 667){
		(*a) += 10;
	}
	else{
		(*a) = 50;
	}
	SDL_BlitSurface(zozor.img, NULL, ecran, &zozor.position);
}

SDL_Surface* switchFullScreen(Uint32 flags){
	SDL_Surface *screen =SDL_GetVideoSurface();
	screen =SDL_SetVideoMode(0, 0, 0, flags);
	if (screen==NULL){
        	fprintf(stderr, "Err / switchFullScreen : changement de format impossible :%s\n",   SDL_GetError());
        	screen=SDL_SetVideoMode(0, 0, 0, flags^SDL_FULLSCREEN);
	}
	return(screen);
}	
	
