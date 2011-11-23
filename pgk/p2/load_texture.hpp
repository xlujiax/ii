#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL_image.h>

GLuint load_texture(const char *filename);
SDL_Surface *loadImage(const char *filename);
