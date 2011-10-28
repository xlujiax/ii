#include <SDL.h>
#include <SDL_opengl.h>

#include "sdl_window.hpp"
#include "timer.hpp"
#include "viewer.hpp"

timer frame_timer;
viewer main_viewer;

int main(int argc, char* argv[])
{
  window wnd;

  wnd.setup_opengl = [](const int width, const int height) {
    glViewport(0, 0, width, height);
    gluOrtho2D(0, width, height, 0);
    glClearColor(0.0, 0.0, 0.0, 0.0);
  };

  if(!wnd.setup(640, 480))
    return 1;

  frame_timer.init();
  main_viewer.init();

  wnd.keydown = [&](const char k) {  };
  wnd.keyup = [&](const char k) {  };

  wnd.frame = [&]() {
    const float delta_time = frame_timer.delta_time();
    main_viewer.animate(delta_time);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    main_viewer.draw();
    SDL_GL_SwapBuffers();
  };

  wnd.main_loop();

  return 0;
}
