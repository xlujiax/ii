compiler = g++-4.5
opengl_libs = -lGL -lGLU -lGLEW -lSDL_image
sdl_libs = `sdl-config --cflags --libs`
error_flags = -Wall -Werror
std_flag = -std=c++0x

libs = $(opengl_libs) $(sdl_libs)
modules = timer.o sdl_window.o

output = viewer.e

all: viewer.e

sdl_window.o: sdl_window.cpp sdl_window.hpp
	$(compiler) $(error_flags) $(std_flag) -c sdl_window.cpp $(libs)

timer.o: timer.cpp timer.hpp
	$(compiler) $(error_flags) $(std_flag) -c timer.cpp $(libs)

$(output): main.cpp $(modules)
	$(compiler) $(error_flags) $(std_flag) main.cpp $(modules) $(libs) -o $(output)

clear:
	rm $(modules) $(output)
