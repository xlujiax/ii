#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
using namespace std;

#include "sdl_window.h"

#include <math.h>

static void repaint()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glBegin(GL_POLYGON);
  
  glEnd();
  SDL_GL_SwapBuffers();
}

static void setup_opengl(const int width, const int height)
{
  float aspect = (float)width / (float)height;

  /* Make the viewport cover the whole window */
  glViewport(0, 0, width, height);

  /* Set the camera projection matrix:
   * field of view: 90 degrees
   * near clipping plane at 0.1
   * far clipping plane at 100.0
   */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(60.0, aspect, 0.1, 100.0);
  /* We're done with the camera, now matrix operations
   * will affect the modelview matrix
   * */
  glMatrixMode(GL_MODELVIEW);

  /* set the clear color to gray */
  glClearColor(0.5, 0.5 ,0.5, 0);

  /* We want z-buffer tests enabled*/
  glEnable(GL_DEPTH_TEST);

  /* Do draw back-facing polygons*/
  glDisable(GL_CULL_FACE);
}


static void main_loop()
{
  SDL_Event event;

  while (1) {
    /* process pending events */
    while( SDL_PollEvent( &event ) ) {
      switch( event.type ) {
        case SDL_KEYDOWN:
          switch ( event.key.keysym.sym ) {
            case SDLK_ESCAPE:
              exit(0);
              break;

            case SDLK_KP_PLUS:
              break;

            case SDLK_KP_MINUS:
              break;

            default:
              //no default key processing
              //(stops compiler warnings for unhandled SDL keydefs
              break;
          }
          break;

        case SDL_MOUSEMOTION:
          break;

        case SDL_QUIT:
          exit (0);
          break;
      }
    }

    /* update the screen */
    repaint();

    /* Wait 50ms to avoid using up all the CPU time */
    SDL_Delay( 50 );
  }
}


int main(int argc, char* argv[])
{
  if(!setup_sdl_window(640, 480))
    return 1;

  setup_opengl(640, 480);

  main_loop();

  return 0;
}
