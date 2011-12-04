#pragma once

#include <GL/glew.h>
#include <SDL.h>

class viewer
{
public:
  void init();
  void draw() const;
  void update(const float delta_time);
};
