#pragma once

#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>
#include "vec.h"

class img
{
  GLuint texId;
public:
  ~img();
  void load(char* file);
  void draw(int x, int y, int sizex, int sizey);
  void draw(int x, int y, vec v) { draw(x, y, v.x, v.y); }
  void draw(vec v, int x, int y) { draw(v.x, v.y, x, y); }
  void draw(vec v, vec u) { draw(v.x, v.y, u.x, u.y); }
};

/* OpenGL texture info */
class gl_texture_t
{
public:
  GLsizei width;
  GLsizei height;

  GLenum format;
  GLint internalFormat;
  GLuint id;

  GLubyte *texels;
};

