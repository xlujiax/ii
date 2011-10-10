#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

struct ball
{
  float x, y, radius;
  float vx, vy;

  float top_boundary, bottom_boundary,
    left_boundary, right_boundary;

  void draw() const;
  void animate(const float dtime);
};
