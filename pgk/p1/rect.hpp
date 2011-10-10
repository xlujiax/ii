#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include "vec.hpp"

struct rect
{
  vec pos, size;

  static bool collide(const rect& a, const rect& b);
};

