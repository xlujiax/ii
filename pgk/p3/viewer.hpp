#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <array>
#include <cmath>

#include <GL/glew.h>
#include <SDL.h>

#include "shader.hpp"
#include "loader.hpp"

class viewer
{
  std::array<float, 16> perspective_matrix() const;
  std::array<float, 16> translation_matrix() const;
  std::array<float, 16> rotation_x_matrix() const;
  std::array<float, 16> rotation_y_matrix() const;
  std::array<float, 16> rotation_z_matrix() const;

  GLuint theProgram;
  GLuint vertexBufferObject;
  GLuint vao;
  
  GLuint perspectiveMatrixUnif;
  GLuint translationMatrixUnif;
  GLuint rotationXMatrixUnif;
  GLuint rotationYMatrixUnif;
  GLuint rotationZMatrixUnif;

  void init_vbo();
  void init_program();

  struct {
    bool w,s,a,d,q,e,r,t;
  } keys;
  float offx, offy, offz, rot_x, rot_y, rot_z;
  Uint8 *keystate;
public:
  void init();
  void draw() const;
  void update(const float delta_time);

  bool keydown(const int c) { return keystate[c]; }
  void set_keystate(Uint8* k) { keystate = k; }
};
