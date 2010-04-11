game:
	gcc -std=c99 -c game.c

curve: utils polygon
	gcc -std=c99 -c curve.c

reduction: curve
	gcc -std=c99 -c reduction.c

hull: utils polygon curve
	gcc -std=c99 -c hull.c

intersection: line curve
	gcc -std=c99 -c intersection.c

polygon: utils
	gcc -std=c99 -c polygon.c

utils:
	gcc -std=c99 -c utils.c

line: utils
	gcc -std=c99 -c line.c

init: intersection reduction curve polygon line hull game
	gcc -std=c99 init.c curve.o reduction.o polygon.o intersection.o utils.o line.o hull.o game.o -lglut -lpng -o game.e

all: init
clear:
	rm *.o *.e