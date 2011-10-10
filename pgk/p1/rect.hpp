#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <array>
#include <algorithm>

#include "vec.hpp"

struct rect
{
  rect();
  
  vec pos, size;

  float color_r, color_g, color_b;
  bool filled;
  bool visible;

  std::array<vec, 4> corners() const;
  
  void draw() const;
  static bool collide(const rect& a, const rect& b);
  bool point_inside(const vec& v) const;

  void stick_to_bottom(const rect&);
  void stick_to_top(const rect&);
  void stick_to_left(const rect&);
  void stick_to_right(const rect&);
};

