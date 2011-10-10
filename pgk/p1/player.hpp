#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include <memory>

#include "rect.hpp"
#include "vec.hpp"

struct player : public rect
{
  vec vel;
  float move_speed;

  rect* top_boundary;
  rect* bottom_boundary;

  player();
  
  void animate(const float dtime);

  void move_up() { vel.y = -move_speed; }
  void move_down() { vel.y = move_speed; }
  void move_up_end() { if(vel.y < 0) vel.y = 0; }
  void move_down_end() { if(vel.y > 0) vel.y = 0; }
};
