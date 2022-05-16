#include "enigme.h"
#include <string.h>
#include <time.h>
/**
  *@file enigme.c
  *@brief Testing Program.
  *@author C Team
  *@version 0.1
  *date Apr 28, 2022
  *
  *Testing programe for enigme
  scrollilng *
  */
void initenigme(enigme *e,enigme *e2,enigme *e3, char *nomfich[]){
 char s1[]="ques1.png",s2[]="ques2.png",s3[]="ques3.png";
	(*e).img=IMG_Load("ques1.png");   
        (*e2).img=IMG_Load("ques2.png");
	(*e3).img=IMG_Load("ques3.png");
	(*e).poscr.x=0;
	(*e).poscr.y=0;                         
	(*e2).poscr.x=0;
	(*e2).poscr.y=0;
	(*e3).poscr.x=0;
	(*e3).poscr.y=0; 
	FILE * f=fopen(nomfich,"a");
	if (f!=NULL){
		fprintf (f,"%s\n%s\n%s\n",s1,s2,s3);                
		fclose(f);
   	}
	else 
		printf ("impossible d'ouvrir le fichier");
}

void afficherenigme(int alea,enigme e, animat z[], SDL_Surface *screen,int anim){       
	if (alea==1){
        	SDL_BlitSurface(e.img,NULL,screen,&e.poscr); 
		for(int i=0;i<7;i++){
			SDL_BlitSurface(z[0].img,NULL,screen,&z[0].posi[i].poscr);
		}
		SDL_BlitSurface(z[1].img,NULL,screen,&z[1].posi[0].poscr);
		
		for(int i=0;i<3;i++){
			SDL_BlitSurface(z[4].img,&z[4].posi[0].posp,screen,&z[4].posi[i].poscr);
		}
		
		for(int i=0;i<4;i++){
			SDL_BlitSurface(z[3].img,&z[3].posi[0].posp,screen,&z[3].posi[i].poscr);
		}

		for(int i=0;i<5;i++){
			SDL_BlitSurface(z[2].img,&z[2].posi[0].posp,screen,&z[2].posi[i].poscr);
		}
	}
	else {
                SDL_BlitSurface(e.img,NULL,screen,&e.poscr);
	}

}

void afficherselec(enigme e,enigme e2,enigme e3, SDL_Surface *screen,int aff){       
	if (aff==1){
        	SDL_BlitSurface(e.img,NULL,screen,&e.poscr);
	}
	else if (aff==2){
        	SDL_BlitSurface(e2.img,NULL,screen,&e2.poscr);
	}
	else if (aff==3){
        	SDL_BlitSurface(e3.img,NULL,screen,&e3.poscr);
	}
}


void initanimation(animat z[]){
	
	z[0].img=IMG_Load("sign+.png");
	z[0].posi[0].poscr.x=350;
	z[0].posi[0].poscr.y=70;
	z[0].posi[1].poscr.x=350;
	z[0].posi[1].poscr.y=670;
	z[0].posi[2].poscr.x=350;
	z[0].posi[2].poscr.y=260;
	z[0].posi[3].poscr.x=350;
	z[0].posi[3].poscr.y=470;
	z[0].posi[4].poscr.x=800;
	z[0].posi[4].poscr.y=70;
	z[0].posi[5].poscr.x=800;
	z[0].posi[5].poscr.y=260;
	z[0].posi[6].poscr.x=800;
	z[0].posi[6].poscr.y=470;

	z[1].img=IMG_Load("signx.png");
	z[1].posi[0].poscr.x=800;
	z[1].posi[0].poscr.y=670;
	
	z[2].img=IMG_Load("cat.png");
	z[2].posi[0].poscr.x=150;
	z[2].posi[0].poscr.y=100;
	z[2].posi[1].poscr.x=600;
	z[2].posi[1].poscr.y=100;
	z[2].posi[2].poscr.x=1050;
	z[2].posi[2].poscr.y=100;
	z[2].posi[3].poscr.x=150;
	z[2].posi[3].poscr.y=300;
	z[2].posi[4].poscr.x=150;
	z[2].posi[4].poscr.y=700;
	z[2].posi[0].posp.x=0;
	z[2].posi[0].posp.y=0;
	z[2].posi[0].posp.w=208;
	z[2].posi[0].posp.h=210;

	z[3].img=IMG_Load("dragon.png");
	z[3].posi[0].poscr.x=150;
	z[3].posi[0].poscr.y=525;
	z[3].posi[1].poscr.x=600;
	z[3].posi[1].poscr.y=700;
	z[3].posi[2].poscr.x=600;
	z[3].posi[2].poscr.y=300;
	z[3].posi[3].poscr.x=1050;
	z[3].posi[3].poscr.y=300;
	z[3].posi[0].posp.x=0;
	z[3].posi[0].posp.y=0;
	z[3].posi[0].posp.w=178;
	z[3].posi[0].posp.h=163;

	z[4].img=IMG_Load("ship.png");
	z[4].posi[0].poscr.x=600;
	z[4].posi[0].poscr.y=525;
	z[4].posi[1].poscr.x=1050;
	z[4].posi[1].poscr.y=700;
	z[4].posi[2].poscr.x=1050;
	z[4].posi[2].poscr.y=525;
	z[4].posi[0].posp.x=0;
	z[4].posi[0].posp.y=0;
	z[4].posi[0].posp.w=174;
	z[4].posi[0].posp.h=165;
}



void animer (animat z[]){
	if (z[2].posi[0].posp.x==832){
               z[2].posi[0].posp.x=0;
	}
	else{
		z[2].posi[0].posp.x=z[2].posi[0].posp.x+208; 
        }
	
	if (z[3].posi[0].posp.x==534){
               z[3].posi[0].posp.x=0;
	}
	else{
		z[3].posi[0].posp.x=z[3].posi[0].posp.x+178; 
        }

	if (z[4].posi[0].posp.x==696){
               z[4].posi[0].posp.x=0;
	}
	else{
		z[4].posi[0].posp.x=z[4].posi[0].posp.x+174; 
        }
}

int enigmealea(SDL_Surface *screen){
	SDL_Event event,event2;
 	int max=3,min=1;
	int continuer=1,alea =-1,anim=0,niv1=1,niv2=1,niv3=1,win1=0,win2=0,win3=0,lose1=0, lose2=0,lose3=0;
	animat z[5];
	initanimation(z);
	enigme e,e2,e3,A,B,C,A1,B1,C1;

	initenigme(&e,&e2,&e3,"fichier.txt"); 

	Im Al;
	Al.img=IMG_Load("allumette.png");
	Al.position.x=682;
	Al.position.y=352;
	Al.zone.x=27;
	Al.zone.y=246;
	

	A.img=IMG_Load("clic.png");
	A.poscr.x=263;
	A.poscr.y=815;
        A.posp.x=0;
	A.posp.y=0;
        A.posp.w=200;
	A.posp.h=256;
        B.img=IMG_Load("clic2.png");
	B.poscr.x=679;
	B.poscr.y=815;
        B.posp.x=0;
	B.posp.y=0;
        B.posp.w=200;
	B.posp.h=256;
        C.img=IMG_Load("clic3.png");
	C.poscr.x=1149;
	C.poscr.y=815;
        C.posp.x=0;
	C.posp.y=0;
        C.posp.w=200;
	C.posp.h=256;

	A1.img=IMG_Load("repA.png");
	A1.poscr.x=55;
	A1.poscr.y=910;
	A1.posp.x=0;
	A1.posp.y=0;
	A1.posp.w=378;
	A1.posp.h=103;
	B1.img=IMG_Load("repB.png");
	B1.poscr.x=648;
	B1.poscr.y=910;
	B1.posp.x=0;
	B1.posp.y=0;
	B1.posp.w=378;
	B1.posp.h=103;
	C1.img=IMG_Load("repC.png");
	C1.poscr.x=1240;
	C1.poscr.y=910;
	C1.posp.x=0;
	C1.posp.y=0;
	C1.posp.w=378;
	C1.posp.h=103;
	
	int ea=0;
        srand(time(NULL));
	alea=(rand()%(max-min+1)+min);
	while (continuer){
		if(alea==2 || alea ==3){ 
			win1=1; 	
			lose1=0;
		}
		while(niv1 && !win1 && !lose1){
			afficherenigme(alea,e,z,screen,anim);
			afficherselec(A1,B1,C1,screen,ea); 
			SDL_Flip(screen);
			animer(z);
			SDL_Delay(50);
			while(SDL_PollEvent(&event)){
				switch(event.type){
					case SDL_QUIT:
						continuer =0;
						niv1=0;
						lose1=1;
						break;
					case SDL_MOUSEMOTION:
						ea=0;
						if (event.motion.x>=A1.poscr.x && event.motion.x<=A1.poscr.x+A1.posp.w && event.motion.y>=A1.poscr.y && event.motion.y<=A1.poscr.y+A1.posp.h){
							ea=1;
						}
						else if (event.motion.x>=B1.poscr.x && event.motion.x<=B1.poscr.x+B1.posp.w && event.motion.y>=B1.poscr.y && event.motion.y<=B1.poscr.y+B1.posp.h){
							ea=2;
						}
						else if (event.motion.x>=C1.poscr.x && event.motion.x<=C1.poscr.x+C1.posp.w && event.motion.y>=C1.poscr.y && event.motion.y<=C1.poscr.y+C1.posp.h){
							ea=3;
						}
						break;
					case SDL_MOUSEBUTTONDOWN:
						if (ea==1){
							lose1=1;
						}
						else if (ea==2){
							lose1=1;
						}
						else if (ea==3){
							win1=1;
						}
						break;
					case SDL_KEYDOWN:
						switch(event.key.keysym.sym){
							case SDLK_ESCAPE:
							case SDLK_e:
								niv1=0;	
								lose1=1;
								break;
						}
						break;
				}					
			}
		}
		if(alea==1)
			{win2=1; lose2=0;win3=1; lose3=0;}
		if (lose1!=1){
			if(alea==3)
				{win2=1; lose2=0;}
			while(niv2 && win1 && !win2 && !lose2){
				
				afficherenigme(alea,e2,z,screen,anim);
				afficherselec(A,B,C,screen,ea); 
				SDL_Flip(screen);
				while(SDL_PollEvent(&event2)){
					switch(event2.type){
						case SDL_QUIT:
							continuer =0;
							niv2=0;
							lose2=1;
							break;
						case SDL_MOUSEMOTION:
							ea=0;
							if (event2.motion.x>=A.poscr.x && event2.motion.x<=A.poscr.x+A.posp.w && event2.motion.y>=A.poscr.y && event2.motion.y<=A.poscr.y+A.posp.h){
								ea=1;
							}
							else if (event2.motion.x>=B.poscr.x && event2.motion.x<=B.poscr.x+B.posp.w && event2.motion.y>=B.poscr.y && event2.motion.y<=B.poscr.y+B.posp.h){
								ea=2;
							}
							else if (event2.motion.x>=C.poscr.x && event2.motion.x<=C.poscr.x+C.posp.w && event2.motion.y>=C.poscr.y && event2.motion.y<=C.poscr.y+C.posp.h){
								ea=3;
							}
							break;
						case SDL_MOUSEBUTTONDOWN:
							if (ea==1){
								win2=1;
							}
							else if (ea==2){
								lose2=1;
							}
							else if (ea==3){
								lose2=1;
							}
							break;
						case SDL_KEYDOWN:
							switch(event2.key.keysym.sym){
								case SDLK_ESCAPE:
								case SDLK_e:
									continuer =0;
									niv2=0;
									lose2=1;
									break;
							}
							break;
					}					
				}
			}
			while(niv3 && win1 && win2 && !win3 && !lose3){
				int attendre=1;
				afficherenigme(alea,e3,z,screen,anim);
				SDL_BlitSurface(Al.img,NULL,screen,&Al.position);
				SDL_Flip(screen);
				while(SDL_PollEvent(&event2)){
					switch(event2.type){
						case SDL_QUIT:
							continuer =0;
							niv3=0;
							lose3=1;
							break;
						case SDL_MOUSEMOTION:
							break;
						case SDL_MOUSEBUTTONDOWN:
							if (event2.motion.x>=Al.position.x-10 && event2.motion.x<=Al.position.x+40 && event2.motion.y>=Al.position.y-5 && event2.motion.y<=Al.position.y+250){
								while(attendre){
									if(Al.position.x==1351 && Al.position.y==580){
										attendre=0;
										SDL_Delay(3000);
									}
									if(Al.position.x<1351){
										Al.position.x=Al.position.x+8;
									}
									else{
										Al.position.x=1351;
									}
									if(Al.position.y<580){
										Al.position.y=Al.position.y+3;
									}
									else{
										Al.position.y=580;
									}
									afficherenigme(alea,e3,z,screen,anim);
									SDL_BlitSurface(Al.img,NULL,screen,&Al.position);
									SDL_Flip(screen);
								}
								win3=1;
							}
							else{
								lose3 = 1;
								win3=0;
							}
							break;
						case SDL_KEYDOWN:
							switch(event2.key.keysym.sym){
								case SDLK_ESCAPE:
								case SDLK_e:
									continuer =0;
									niv3=0;
									lose3=1;
									break;
							}
							break;
					}					
				}
			}
			if (lose2!=1 && lose3!=1){
				int fin=1;
				enigme F;
				F.img=IMG_Load("win.png");
        			F.poscr.x=0;
				F.poscr.y=0;
				while(fin){
					SDL_BlitSurface(F.img,NULL,screen,&F.poscr);
					SDL_Flip(screen);
					SDL_Delay(2000);
					fin=0;
					return 1;
				}
			}
			else {
				int fin=1;
				enigme F;
				F.img=IMG_Load("lose.png");
        			F.poscr.x=0;
				F.poscr.y=0;
				while(fin){
					SDL_BlitSurface(F.img,NULL,screen,&F.poscr);
					SDL_Flip(screen);
					SDL_Delay(2000);
					fin=0;
					return 0;
				}
			}
		}
		else {
			int fin=1;
			enigme F;
			F.img=IMG_Load("lose.png");
        		F.poscr.x=0;
			F.poscr.y=0;
			while(fin){
				SDL_BlitSurface(F.img,NULL,screen,&F.poscr);
				SDL_Flip(screen);
				SDL_Delay(2000);
				fin=0;
				return 0;
			}
		}
	}
}
