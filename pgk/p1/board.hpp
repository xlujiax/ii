#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

#include "rect.hpp"

struct board : public drawable_rect
{
  board();
};
