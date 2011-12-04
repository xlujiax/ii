#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <SDL.h>

#include "sdl_window.hpp"
#include "timer.hpp"
#include "shader.hpp"
#include "viewer.hpp"

timer frame_timer;
viewer main_viewer;

GLuint theProgram;

void InitializeProgram()
{
  std::vector<GLuint> shaderList;

  shaderList.push_back(LoadShader(GL_VERTEX_SHADER, "shaders/sh.vert"));
  shaderList.push_back(LoadShader(GL_FRAGMENT_SHADER, "shaders/sh.frag"));

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

  main_viewer.init();
  main_viewer.init();

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
    const float delta_time = frame_timer.delta_time();
    main_viewer.update(delta_time);
    main_viewer.draw();

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
