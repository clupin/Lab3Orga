all: Funcion1 Funcion2 Programa1 Programa2 funcion1_vect Funcion2_vect programa1_vect Programa2_vect

Funcion1: Funcion1.c
	gcc -o Funcion1 Funcion1.c -lm 

Funcion2: Funcion2.c
	gcc -o Funcion2 Funcion2.c -lm

Programa1: Programa1.c
	gcc -o Programa1 Programa1.c -lm -std=c99

Programa2: Programa2.c
	gcc -o Programa2 Programa2.c -lm -std=c99

funcion1_vect: funcion1_vect.c
	gcc -o funcion1_vect funcion1_vect.c -lm -L. cargarchivo.c -msse -msse2 -msse3 

Funcion2_vect: Funcion2_vect.c
	gcc -o Funcion2_vect Funcion2_vect.c -lm -std=c99 -msse -msse2 -msse3

programa1_vect: programa1_vect.c
	gcc -o programa1_vect programa1_vect.c -lm -std=c99 -msse -msse2 -msse3

Programa2_vect: Programa2_vect.c
	gcc -o Programa2_vect Programa2_vect.c -lm -std=c99 -msse -msse2 -msse3
