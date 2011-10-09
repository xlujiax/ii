#pragma once

#include "SDL.h"
#include "SDL_opengl.h"

#include <iostream>
#include <cstdio>

bool setup_sdl_window(const int width, const int height);
void setup_opengl(const int width, const int height);
void handle_resize(const int width, const int height);
