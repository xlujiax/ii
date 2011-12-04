compiler = g++-4.5
opengl_libs = -lGL -lGLU -lGLEW -lSDL_image
sdl_libs = `sdl-config --cflags --libs`
error_flags = -Wall -Werror
std_flag = -std=c++0x

libs = $(opengl_libs) $(sdl_libs)
modules = timer.o sdl_window.o shader.o viewer.o loader.o

output = viewer.e

all: viewer.e

%.o: %.cpp %.hpp
	$(compiler) $(error_flags) $(std_flag) -c $< $(libs)

$(output): main.cpp $(modules)
	$(compiler) $(error_flags) $(std_flag) $< $(modules) $(libs) -o $(output)

clear:
	rm $(modules) $(output)
