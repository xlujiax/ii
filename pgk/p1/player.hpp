#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include "board.hpp"

struct player
{
  float x, y;
  float vy;
  float speed;

  float sizex, sizey;

  float top_boundary, bottom_boundary;

  player();
  
  void draw() const;
  void animate(const float dtime);

  void move_up() { vy = -speed; }
  void move_down() { vy = speed; }
  void move_up_end() { if(vy < 0) vy = 0; }
  void move_down_end() { if(vy > 0) vy = 0; }
};