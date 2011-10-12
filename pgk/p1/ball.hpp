#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include <memory>
#include "rect.hpp"
#include "player.hpp"
#include "vec.hpp"

#include <iostream>

struct ball : public drawable_rect
{
  ball();
  
  vec vel;
  float speed;

  void normalize_speed();
  
  rect* top_boundary;
  rect* bottom_boundary;
  player* right_paddle;
  player* left_paddle;

  void animate(const float dtime);
private:
  void handle_collision_with_player(const player& paddle);
};
