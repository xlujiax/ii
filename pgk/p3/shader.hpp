#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <SDL.h>

GLuint LoadShader(GLenum eShaderType, const std::string &strFilename);
GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile);
GLuint CreateProgram(const std::vector<GLuint> &shaderList);
