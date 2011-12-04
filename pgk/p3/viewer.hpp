#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <array>

#include <GL/glew.h>
#include <SDL.h>

#include "shader.hpp"

class viewer
{
  std::array<float, 16> perspective_matrix() const;
  std::array<float, 16> translation_matrix() const;
  std::array<float, 16> rotation_matrix() const;

  GLuint theProgram;
  GLuint vertexBufferObject;
  GLuint vao;
  
  GLuint offsetUniform;
  GLuint perspectiveMatrixUnif;
  GLuint translationMatrixUnif;
  GLuint rotationMatrixUnif;

  void init_vbo();
  void init_program();

  struct {
    bool w,s,a,d,e,r;
  } keys;
  float offx, offy, offz;
public:
  void init();
  void draw() const;
  void update(const float delta_time);

  void keydown(const char);
  void keyup(const char);
};
