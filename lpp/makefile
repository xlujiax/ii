FLAGS=-Wall -std=c99 -pedantic
OBJ=bezier.o graph.o quadclip.o reduction.o samples.o utils.o roots.o gui.o

bezier:
	gcc $(FLAGS) -c bezier.c

samples:
	gcc $(FLAGS) -c samples.c

graph: bezier
	gcc $(FLAGS) -c graph.c

quadclip: bezier reduction roots
	gcc $(FLAGS) -c quadclip.c

reduction: bezier utils
	gcc $(FLAGS) -c reduction.c

utils:
	gcc $(FLAGS) -c utils.c

roots: bezier
	gcc $(FLAGS) -c roots.c

gui: graph reduction quadclip samples
	gcc $(FLAGS) -c gui.c

init: game
	gcc $(FLAGS) init.c $(OBJ) -lglut -lpng -o lpp.e

all: init
clear:
	rm *.o *.e