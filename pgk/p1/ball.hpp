#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include <memory>
#include "rect.hpp"
#include "vec.hpp"

struct ball : public rect
{
  ball();
  
  vec vel;
  
  rect* top_boundary;
  rect* bottom_boundary;
  rect* right_paddle;
  rect* left_paddle;

  void animate(const float dtime);
};
