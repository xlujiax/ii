#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <SDL.h>

#include "sdl_window.hpp"
#include "timer.hpp"
#include "shader.hpp"

timer frame_timer;


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

void InitializeProgram()
{
  std::vector<GLuint> shaderList;

  shader vertex_shader(GL_VERTEX_SHADER, "shaders/sh.vert");
  shader fragment_shader(GL_FRAGMENT_SHADER, "shaders/sh.frag");

  shaderList.push_back(vertex_shader.get_id());
  shaderList.push_back(fragment_shader.get_id());

  theProgram = CreateProgram(shaderList);
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
