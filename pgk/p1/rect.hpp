#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include <array>
#include <algorithm>

#include "vec.hpp"

struct rect
{
  vec pos, size;

  std::array<vec, 4> corners() const;
  
  void draw() const;
  static bool collide(const rect& a, const rect& b);
  bool point_inside(const vec& v) const;
};

