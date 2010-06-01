FLAGS=-Wall -std=c99 -pedantic
OBJ=bezier.o graph.o quadclip.o reduction.o utils.o roots.o game.o

bezier:
	gcc $(FLAGS) -c bezier.c

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

game: graph reduction quadclip
	gcc $(FLAGS) -c game.c

init: game
	gcc $(FLAGS) init.c $(OBJ) -lglut -lpng -o game.e

all: init
clear:
	rm *.o *.e