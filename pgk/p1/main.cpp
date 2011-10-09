#include <SDL.h>
#include <SDL_opengl.h>

#include "sdl_window.hpp"
#include "timer.hpp"
#include "game.hpp"

// poznizsze obiekty musza byc globalne; jesli sa w funkcji main to wystepuje blad:
// error: cannot convert ‘main(int, char**)::<lambda(char)>’ to ‘void (*)(char)’ in assignment
game pong;
timer frame_timer;

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

  pong.init();
  frame_timer.init();

  wnd.keydown = [&](const char k) { pong.keydown(k); };
  wnd.keyup = [&](const char k) { pong.keyup(k); };

  wnd.frame = [&]() {
    const float delta_time = frame_timer.delta_time();
    pong.animate(delta_time);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    pong.draw();

    SDL_GL_SwapBuffers();
  };

  wnd.main_loop();

  return 0;
}
