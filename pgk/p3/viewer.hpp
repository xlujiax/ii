#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <SDL.h>

#include "shader.hpp"

class viewer
{
public:
  void init();
  void draw() const;
  void update(const float delta_time);
};
