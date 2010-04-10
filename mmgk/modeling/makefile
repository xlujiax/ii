OPT=-Wall -std=c99 -pedantic -g
OBJ=control.o ncs.o modeling.o

control:
	gcc $(OPT) -c control.c

ncs: control
	gcc $(OPT) -c ncs.c

modeling: ncs
	gcc $(OPT) -c modeling.c

main: modeling
	gcc $(OPT) $(OBJ) main.c -lglut -o modeling.e

all: main

clear:
	rm *.o *.e