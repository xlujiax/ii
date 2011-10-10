#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include <memory>
#include "rect.hpp"
#include "vel.hpp"

struct ball
{
  ball();
  
  float vel;
  
  std::shared_ptr<rect> top_boundary;
  std::shared_ptr<rect> bottom_boundary;
  std::shared_ptr<rect> right_player;
  std::shared_ptr<rect> left_player;

  void animate(const float dtime);
};
