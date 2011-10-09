#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

struct ball
{
  float x, y, radius;
  float vx, vy;

  void draw() const;
};
