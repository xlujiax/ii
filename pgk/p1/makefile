opengl_libs = -lGL -lGLU
sdl_libs = `sdl-config --cflags --libs`
error_flags = -Wall -Werror

libs = $(opengl_libs) $(sdl_libs)

all: pong.e

timer.o: timer.cpp timer.h
	g++ $(error_flags) -c timer.cpp $(libs)

sdl_window.o: sdl_window.cpp sdl_window.h
	g++ $(error_flags) -c sdl_window.cpp $(libs)

pong.e: pong.cpp sdl_window.o timer.o
	g++ $(error_flags) pong.cpp sdl_window.o timer.o $(libs) -o pong.e