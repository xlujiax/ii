OPT=-Wall
OBJ=modeling.o

modeling:
	g++ $(OPT) -c modeling.cpp

main: modeling
	g++ $(OPT) $(OBJ) main.cpp -lglut -o modeling.e

all: main

clear:
	rm *.o *.e