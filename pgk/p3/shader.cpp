#include "shader.hpp"

shader::shader(GLenum eShaderType, const std::string& file)
{
  id = compile_shader(eShaderType, file_contents(file));
}

shader::~shader()
{
  glDeleteShader(id);
}

std::string shader::file_contents(const std::string& file)
{
  std::ifstream shaderFile(file.c_str());
  std::stringstream shaderData;
  shaderData << shaderFile.rdbuf();
  return shaderData.str();
}

GLuint shader::compile_shader(GLenum eShaderType, const std::string &strShaderFile)
{
  GLuint shader_id = glCreateShader(eShaderType);
  const char *strFileData = strShaderFile.c_str();
  glShaderSource(shader_id, 1, &strFileData, NULL);

  glCompileShader(shader_id);

  GLint status;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE)
  {
    GLint infoLogLength;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &infoLogLength);

    GLchar *strInfoLog = new GLchar[infoLogLength + 1];
    glGetShaderInfoLog(shader_id, infoLogLength, NULL, strInfoLog);

    const char *strShaderType = NULL;
    switch(eShaderType)
    {
      case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
      case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
      case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
    }

    std::cerr << "Compile failure in " << strShaderType << " shader:\n" <<
      strInfoLog << "\n";
    delete[] strInfoLog;
  }

  return shader_id;
}
