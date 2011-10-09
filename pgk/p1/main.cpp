#include <SDL.h>
#include <SDL_opengl.h>

#include "sdl_window.hpp"
#include "timer.hpp"
#include "game.hpp"

#include <iostream>
using namespace std;

game pong;
timer frame_timer;

void setup_opengl(const int width, const int height)
{
  glViewport(0, 0, width, height);
  gluOrtho2D(0, width, height, 0);
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void keyup(const char k)
{
  pong.keyup(k);
}

void keydown(const char k)
{
  pong.keydown(k);
}

void frame()
{
  const float delta_time = frame_timer.delta_time();
  pong.animate(delta_time);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  pong.draw();

  SDL_GL_SwapBuffers();
}

int main(int argc, char* argv[])
{
  window wnd;

  wnd.setup_opengl = setup_opengl;

  if(!wnd.setup(640, 480))
    return 1;

  pong.init();
  frame_timer.init();

  // why not: wnd.keydown = [&](const key k) { pong.keydown(k); } ?
  wnd.keydown = keydown;
  wnd.keyup = keyup;

  wnd.frame = frame;

  wnd.main_loop();

  return 0;
}
