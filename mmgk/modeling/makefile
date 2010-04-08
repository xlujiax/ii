OPT=-Wall -std=c99 -pedantic
OBJ=control.o modeling.o

control:
	gcc $(OPT) -c control.c

modeling: control
	gcc $(OPT) -c modeling.c

main: modeling
	gcc $(OPT) $(OBJ) main.c -lglut -o modeling.e

all: main

clear:
	rm *.o *.e