prog:entete.o enigme.o perso.o minimap.o background.o fonctions.o main.o
	gcc entete.o enigme.o perso.o minimap.o background.o fonctions.o main.o -o prog -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g
main.o:main.c
	gcc -c main.c -g
entete.o:entete.c
	gcc -c entete.c -g
enigme.o:enigme.c
	gcc -c enigme.c -g
perso.o:perso.c
	gcc -c perso.c -g
minimap.o:minimap.c
	gcc -c minimap.c -g
background.o:background.c
	gcc -c background.c -g
fonctions.o:fonctions.c
	gcc -c fonctions.c -g


