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

  enum class edge
  {
    bottom, top, left, right
  };

  vec center() const;
  vec middle_of(edge e) const;

  void stick_to(edge e, const rect&);

  static bool collide(const rect& a, const rect& b);
private:
  bool point_inside(const vec& v) const;
};

struct drawable_rect : public rect
{
  drawable_rect();

  float color_r, color_g, color_b;
  bool filled;
  bool visible;

  void draw() const;
};
