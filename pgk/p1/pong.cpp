#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
using namespace std;

#include "sdl_window.hpp"
#include "timer.hpp"
#include "player.hpp"

timer frame_timer;
player p1, p2;

static void init()
{
  p1.x = 100;
  p1.y = 100;

  p2.x = 300;
  p2.y = 300;

  frame_timer.init();
}

static void draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f(1.0,1.0,1.0);
  p1.draw();

  glColor3f(1.0,0.0,1.0);
  p2.draw();

  SDL_GL_SwapBuffers();
}

static void animate()
{
  const float dtime = frame_timer.delta_time();
  
  p1.animate(dtime);
  p2.animate(dtime);
}

static void setup_opengl(const int width, const int height)
{
  glViewport(0, 0, width, height);
  gluOrtho2D(0, width, height, 0);
  glClearColor(0.0, 0.0, 0.0, 0.0);
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

	    case 'a':
	      p1.move_up();
	      break;

	    case 'z':
	      p1.move_down();
	      break;
	      
	    case 'k':
	      p2.move_up();
	      break;

	    case 'm':
	      p2.move_down();
	      break;

            default:
              break;
          }
          break;
	case SDL_KEYUP:
          switch(event.key.keysym.sym)
	  {
	    case 'a':
	      p1.move_up_end();
	      break;
	    case 'z':
	      p1.move_down_end();
	      break;
	    case 'k':
	      p2.move_up_end();
	      break;
	    case 'm':
	      p2.move_down_end();
	      break;
	    default:
              break;
          }
          break;
        case SDL_QUIT:
          exit (0);
          break;
      }
    }
    animate();
    draw();
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
