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

  enum class line_type
  {
    vertex, normal, face, comment, unclassified
  };

  line_type classify_line(const std::string& line) const;
  std::vector<vec3> obj_format::read_vertices(const std::vector<std::string>& lines) const;
public:
  void read_from_file(const char* filename);
  void draw() const;
};
