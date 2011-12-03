#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <SDL.h>

#include "sdl_window.hpp"
#include "timer.hpp"

timer frame_timer;

GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile)
{
  GLuint shader = glCreateShader(eShaderType);
  const char *strFileData = strShaderFile.c_str();
  glShaderSource(shader, 1, &strFileData, NULL);

  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE)
  {
    GLint infoLogLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

    GLchar *strInfoLog = new GLchar[infoLogLength + 1];
    glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

    const char *strShaderType = NULL;
    switch(eShaderType)
    {
      case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
      case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
      case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
    }

    fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
    delete[] strInfoLog;
  }

  return shader;
}


GLuint CreateProgram(const std::vector<GLuint> &shaderList)
{
  GLuint program = glCreateProgram();

  for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
    glAttachShader(program, shaderList[iLoop]);

  glLinkProgram(program);

  GLint status;
  glGetProgramiv (program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE)
  {
    GLint infoLogLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

    GLchar *strInfoLog = new GLchar[infoLogLength + 1];
    glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
    fprintf(stderr, "Linker failure: %s\n", strInfoLog);
    delete[] strInfoLog;
  }

  for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
    glDetachShader(program, shaderList[iLoop]);

  return program;
}

GLuint theProgram;

const std::string strVertexShader(
  "#version 330\n"
  "layout(location = 0) in vec4 position;\n"
  "void main()\n"
  "{\n"
  "   gl_Position = position;\n"
  "}\n"
                                  );

const std::string strFragmentShader(
  "#version 330\n"
  "out vec4 outputColor;\n"
  "void main()\n"
  "{\n"
  "   outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
  "}\n"
                                    );


void InitializeProgram()
{
  std::vector<GLuint> shaderList;

  shaderList.push_back(CreateShader(GL_VERTEX_SHADER, strVertexShader));
  shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, strFragmentShader));

  theProgram = CreateProgram(shaderList);

  std::for_each(shaderList.begin(), shaderList.end(), glDeleteShader);
}

const float vertexPositions[] = {
  0.75f, 0.75f, 0.0f, 1.0f,
  0.75f, -0.75f, 0.0f, 1.0f,
  -0.75f, -0.75f, 0.0f, 1.0f,
};

GLuint positionBufferObject;
GLuint vao;


void InitializeVertexBuffer()
{
  glGenBuffers(1, &positionBufferObject);

  glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int main(int argc, char* argv[])
{
  window wnd;

  wnd.setup_opengl = [](const int width, const int height) {
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  };

  if(!wnd.setup(640, 480))
    return 1;
  
  glewInit();

  InitializeProgram();
  InitializeVertexBuffer();

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  frame_timer.init();

  wnd.keydown = [&](const char k) { };
  wnd.keyup = [&](const char k) { };

  wnd.mouseup = [&]() { };
  wnd.mousedown = [&](
    const float x, const float y)
    {
    };

  wnd.mousewheelup = [&]() {  };
  wnd.mousewheeldown = [&]() {  };

  wnd.mousemotion = [&](
    const float x, const float y)
    {
    };

  wnd.frame = [&]() {
    // const float delta_time = frame_timer.delta_time();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(theProgram);

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
    glUseProgram(0);


    SDL_GL_SwapBuffers();

    const int gl_error = glGetError();
    if(gl_error != GL_NO_ERROR)
    {
      printf("OpenGL error (main.cpp): %s\n", gluErrorString(gl_error));
      exit(0);
    }
  };

  wnd.main_loop();

  return 0;
}
