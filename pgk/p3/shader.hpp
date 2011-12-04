#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <SDL.h>

class shader
{
  GLuint id;
  static std::string file_contents(const std::string& file);
  static GLuint compile_shader(GLenum eShaderType, const std::string &strShaderFile);
public:
  shader(GLenum eShaderType, const std::string& file);
  ~shader();
  GLuint get_id() const { return id; }
};
