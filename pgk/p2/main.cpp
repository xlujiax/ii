#include <GL/glew.h>
#include <SDL.h>

#include "sdl_window.hpp"
#include "timer.hpp"
#include "viewer.hpp"

timer frame_timer;
viewer main_viewer;

int main(int argc, char* argv[])
{
  window wnd;

  wnd.setup_opengl = [](const int width, const int height) {
    GLfloat light_diffuse[] = {0.8, 0.5, 0.5, 1.0};
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(40.0, // field of view in degrees
      4.0 / 3.0,         // aspect ratio
      1.0,               // z near
      10.0               // z far
		   );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,  // eye
      0.0, 0.0, 0.0,          // at
      0.0, 1.0, 0.0           // up is in positive Y direction
	      );

    glewInit();
    
    glShadeModel(GL_FLAT);
  };

  if(!wnd.setup(640, 480))
    return 1;

  frame_timer.init();
  main_viewer.init();

  wnd.keydown = [&](const char k) { main_viewer.keydown(k); };
  wnd.keyup = [&](const char k) { main_viewer.keyup(k); };
  
  wnd.mouseup = [&]() { main_viewer.mouseup(); };
  wnd.mousedown = [&]() { main_viewer.mousedown(); };

  wnd.mousewheelup = [&]() { main_viewer.mousewheelup(); };
  wnd.mousewheeldown = [&]() { main_viewer.mousewheeldown(); };

  wnd.mousemotion = [&](
    const float x, const float y,
    const float xrel, const float yrel)
    {
      main_viewer.mousemotion(x, y, xrel, yrel);
    };

  wnd.frame = [&]() {
    const float delta_time = frame_timer.delta_time();
    main_viewer.animate(delta_time);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
