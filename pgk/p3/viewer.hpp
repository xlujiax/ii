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

  enum ShaderSet
    {
      all_white = 0,
      normals = 1,
      height_map = 2
    };

  ShaderSet active_shader_set;
  GLuint shader_programs[3];

  GLuint vertexBufferObject;
  GLuint vao;
  
  GLuint perspectiveMatrixUnif[3];
  GLuint translationMatrixUnif[3];
  GLuint rotationXMatrixUnif[3];
  GLuint rotationYMatrixUnif[3];
  GLuint rotationZMatrixUnif[3];
  GLuint dirLightsUnif[3];
  GLuint numLightsUnif[3];

  void init_vbo();
  void init_program();

  float mouse_move_x;
  float mouse_move_y;
  float last_mouse_x;
  float last_mouse_y;
  bool mouse_click;
  float offx, offy, offz, rot_x, rot_y, rot_z;
  Uint8 *keystate;
  loader map;
public:
  void init();
  void draw() const;
  void update(const float delta_time);

  void mousemotion(const float x, const float y);
  void mousedown(const float x, const float y);
  void mouseup();
  bool keydown(const int c) const { return keystate[c]; }
  void set_keystate(Uint8* k) { keystate = k; }
};
