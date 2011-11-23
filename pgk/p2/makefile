compiler = g++-4.5
opengl_libs = -lGL -lGLU -lGLEW -lSDL_image
sdl_libs = `sdl-config --cflags --libs`
error_flags = -Wall -Werror
std_flag = -std=c++0x

libs = $(opengl_libs) $(sdl_libs)
modules = timer.o sdl_window.o obj_format.o viewer.o load_texture.o vec.o

output = viewer.e

all: viewer.e

sdl_window.o: sdl_window.cpp sdl_window.hpp
	$(compiler) $(error_flags) $(std_flag) -c sdl_window.cpp $(libs)

timer.o: timer.cpp timer.hpp
	$(compiler) $(error_flags) $(std_flag) -c timer.cpp $(libs)

vec.o: vec.cpp vec.hpp
	$(compiler) $(error_flags) $(std_flag) -c vec.cpp $(libs)

load_texture.o: load_texture.cpp load_texture.hpp
	$(compiler) $(error_flags) $(std_flag) -c load_texture.cpp $(libs)

obj_format.o: obj_format.cpp obj_format.hpp
	$(compiler) $(error_flags) $(std_flag) -c obj_format.cpp $(libs)

viewer.o: viewer.cpp viewer.hpp
	$(compiler) $(error_flags) $(std_flag) -c viewer.cpp $(libs)

$(output): main.cpp $(modules)
	$(compiler) $(error_flags) $(std_flag) main.cpp $(modules) $(libs) -o $(output)

clear:
	rm $(modules) $(output)
