window:
	g++ -c window.cpp

img:
	g++ -c img.cpp

ncs:
	g++ -c ncs.cpp

game: window img ncs
	g++ -c game.cpp

init: window game
	g++ init.cpp window.o img.o game.o ncs.o -lglut -lpng -o game.e

all: init
clear:
	rm *.o *.e