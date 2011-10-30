#pragma once

#include <GL/glew.h>
#include <cstdio>
#include <string>
#include <cassert>
#include <vector>
#include <map>

class obj_format
{
private:
  std::vector<std::string> file_to_memory(const char* filename, const unsigned int max_line_len = 100) const;
public:
  void read_from_file(const char* filename);
  void draw() const;
};
