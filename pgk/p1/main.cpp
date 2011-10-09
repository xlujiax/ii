#include <SDL.h>
#include <SDL_opengl.h>

#include "sdl_window.hpp"
#include "timer.hpp"
#include "game.hpp"

game pong;
timer frame_timer;

static void init()
{
  frame_timer.init();
  pong.init();
}

static void frame()
{
  const float delta_time = frame_timer.delta_time();
  pong.animate(delta_time);
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  pong.draw();

  SDL_GL_SwapBuffers();
}

static void main_loop()
{
  SDL_Event event;

  while(true)
  {
    while(SDL_PollEvent(&event))
    {
      switch(event.type) {
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym)
	  {
            case SDLK_ESCAPE:
              exit(0);
              break;

            default:
	      pong.keydown(event.key.keysym.sym);
              break;
          }
          break;
	case SDL_KEYUP:
	  pong.keyup(event.key.keysym.sym);
          break;
	case SDL_VIDEORESIZE:
	  handle_resize(event.resize.w, event.resize.h);
	  break;
        case SDL_QUIT:
          exit(0);
          break;
      }
    }

    frame();
  }
}


int main(int argc, char* argv[])
{
  if(!setup_sdl_window(640, 480))
    return 1;

  setup_opengl(640, 480);

  init();

  main_loop();

  return 0;
}
