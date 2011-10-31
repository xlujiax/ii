#pragma once

#include <GL/glew.h>
#include <cstdio>
#include <string>
#include <cassert>
#include <vector>
#include <map>

struct vec3
{
  float x, y, z;
};

struct vertex
{
  float x, y, z;
  float nx, ny, nz; // normal
  float u, v;       // texture
};

class obj_format
{
private:
  GLuint vertices_vbo;
  GLuint indices_vbo;

  std::vector<vertex> vertices; // full vertices
  std::vector<GLuint> indices; // faces (consecutive fours)

  std::vector<std::string> file_to_memory(const char* filename, const unsigned int max_line_len = 100) const;

  enum class line_type
  {
    vertex, normal, texture, face, comment, unclassified
  };

  line_type classify_line(const std::string& line) const;
  std::vector<vec3> read_vertices(const std::vector<std::string>& lines) const;
  std::vector<vec3> read_normals(const std::vector<std::string>& lines) const;
  std::vector<vec3> read_textures(const std::vector<std::string>& lines) const;
  std::vector<vertex> pack_into_vertex_structure(
    const std::vector<std::string>& lines,
    const std::vector<vec3>& vs,
    const std::vector<vec3>& ns,
    const std::vector<vec3>& ts
						 ) const;
  std::vector<GLuint> read_indices(const std::vector<std::string>& lines,
    const std::vector<vertex>& nvs) const;
public:
  void read_from_file(const char* filename);
  void draw() const;
};
