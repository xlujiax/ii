#pragma once

#include <GL/glew.h>
#include "SDL.h"

#include <iostream>

struct window
{
private:
  const SDL_VideoInfo* video;
  int get_bits_per_pixel() { return video->vfmt->BitsPerPixel; }
  void handle_resize(const int width_param, const int height_param);
public:
  int width;
  int height;
  bool setup(const int width_param, const int height_param);

  void (*setup_opengl)(const int width, const int height);
  void (*keyup)(const char);
  void (*keydown)(const char);
  void (*mousewheelup)();
  void (*mousewheeldown)();
  void (*mouseup)();
  void (*mousedown)(const float x, const float y);
  void (*mousemotion)(const float x, const float y);
  void (*frame)();

  void main_loop();
};
