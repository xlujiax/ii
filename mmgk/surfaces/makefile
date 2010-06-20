all: main

surface:
	gcc -c surface.c -std=c99

demo:
	gcc -c demo.c -std=c99

main: surface demo
	gcc main.c demo.o surface.o -std=c99 -lglut -lGLU -o main.e