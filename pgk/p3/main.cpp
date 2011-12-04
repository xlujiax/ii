#include <fstream>
#include <sstream>

#include "sdl_window.hpp"
#include "timer.hpp"
#include "viewer.hpp"

timer frame_timer;
viewer main_viewer;

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
