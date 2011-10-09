opengl_libs = -lGL -lGLU
sdl_libs = `sdl-config --cflags --libs`
error_flags = -Wall -Werror
std_flag = -std=c++0x

libs = $(opengl_libs) $(sdl_libs)
modules = player.o timer.o sdl_window.o board.o ball.o game.o

output = pong.e

all: pong.e

player.o: player.cpp player.hpp
	g++ $(error_flags) $(std_flag) -c player.cpp $(libs)

board.o: board.cpp board.hpp
	g++ $(error_flags) $(std_flag) -c board.cpp $(libs)

ball.o: ball.cpp ball.hpp
	g++ $(error_flags) $(std_flag) -c ball.cpp $(libs)

timer.o: timer.cpp timer.hpp
	g++ $(error_flags) $(std_flag) -c timer.cpp $(libs)

sdl_window.o: sdl_window.cpp sdl_window.hpp
	g++ $(error_flags) $(std_flag) -c sdl_window.cpp $(libs)

game.o: game.cpp game.hpp
	g++ $(error_flags) $(std_flag) -c game.cpp $(libs)

pong.e: main.cpp $(modules)
	g++ $(error_flags) $(std_flag) main.cpp $(modules) $(libs) -o $(output)

clear:
	rm $(modules)