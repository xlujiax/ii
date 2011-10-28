#pragma once

#include <GL/glew.h>
#include <cstdio>
#include <string>
#include <cassert>
#include <vector>
#include <map>

struct obj_format
{
  void read_from_file(const char* filename);
  void draw() const;
};
