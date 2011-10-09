opengl_libs = -lGL -lGLU
sdl_libs = `sdl-config --cflags --libs`
error_flags = -Wall -Werror

libs = $(opengl_libs) $(sdl_libs)

all: pong.e

sdl_window.o: sdl_window.cpp sdl_window.h
	g++ $(error_flags) -c sdl_window.cpp $(libs)

pong.e: pong.cpp sdl_window.o
	g++ $(error_flags) pong.cpp sdl_window.o $(libs) -o pong.e