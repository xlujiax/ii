#pragma once

#include <GL/glew.h>
#include "SDL.h"

#include <iostream>

struct window
{
private:
  const SDL_VideoInfo* video;
  int get_bits_per_pixel() { return video->vfmt->BitsPerPixel; }
  void handle_resize(const int width, const int height);
public:
  bool setup(const int width, const int height);

  void (*setup_opengl)(const int width, const int height);
  void (*keyup)(const char);
  void (*keydown)(const char);
  void (*mouseup)();
  void (*mousedown)();
  void (*mousemotion)(const int x, const int y);
  void (*frame)();

  void main_loop();
};
