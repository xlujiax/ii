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
  GLuint theProgram;
  GLuint vertexBufferObject;
  GLuint vao;
  
  GLuint offsetUniform;
  GLuint perspectiveMatrixUnif;

  void init_vbo();
  void init_program();

  struct {
    bool w,s,a,d;
  } keys;
  float offx, offy;
public:
  void init();
  void draw() const;
  void update(const float delta_time);

  void keydown(const char);
  void keyup(const char);
};
