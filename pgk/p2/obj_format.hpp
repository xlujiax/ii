#pragma once

#include <GL/glew.h>
#include <cstdio>

struct obj_format
{
  void read_from_file(const char* filename);
  void draw() const;
};
