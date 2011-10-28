#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <cstdio>

struct obj_format
{
  void read_from_file(const char* filename);
  void draw() const;
};
