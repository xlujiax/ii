compiler = g++-4.5
opengl_libs = -lGL -lGLU -lGLEW -lSDL_image
sdl_libs = `sdl-config --cflags --libs`
error_flags = -Wall -Werror
std_flag = -std=c++0x

libs = $(opengl_libs) $(sdl_libs)
modules = timer.o sdl_window.o shader.o viewer.o loader.o

all: viewer.e

timer.o: timer.cpp timer.hpp
	$(compiler) $(error_flags) $(std_flag) -c $< $(libs)

sdl_window.o: sdl_window.cpp sdl_window.hpp
	$(compiler) $(error_flags) $(std_flag) -c $< $(libs)

shader.o: shader.cpp shader.hpp
	$(compiler) $(error_flags) $(std_flag) -c $< $(libs)

viewer.o: viewer.cpp viewer.hpp
	$(compiler) $(error_flags) $(std_flag) -c $< $(libs)

loader.o: loader.cpp loader.hpp
	$(compiler) $(error_flags) $(std_flag) -c $< $(libs)

viewer.e: main.cpp $(modules)
	$(compiler) $(error_flags) $(std_flag) $< $(modules) $(libs) -o viewer.e

clear:
	rm -f $(modules) viewer.e
