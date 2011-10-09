#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

struct board
{
  int x, y, sizex, sizey;
  void draw() const;
};
