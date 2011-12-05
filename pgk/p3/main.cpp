#include <iostream>

#include "sdl_window.hpp"
#include "timer.hpp"
#include "viewer.hpp"

timer frame_timer;
viewer main_viewer;
window wnd;

int main(int argc, char* argv[])
{
  wnd.setup_opengl = [](const int width, const int height) {
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
  };

  if(!wnd.setup(640, 480))
    return 1;

  glewInit();

  main_viewer.init();
  frame_timer.init();

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
    main_viewer.set_keystate(wnd.get_keystate());

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
