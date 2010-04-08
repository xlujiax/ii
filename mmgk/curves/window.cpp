#include "window.h"

Window::Window(int w, int h, int argc, char** argv)
{
  width = w;
  height = h;
  
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutCreateWindow("simple game");

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glEnable(GL_DEPTH_TEST);
  glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);

  // antialiasing
  glEnable (GL_LINE_SMOOTH);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
  glHint (GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
  glHint (GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
}

void Window::setKeyboardFunc(void (*func)(unsigned char key,
                                   int x, int y))
{
  glutKeyboardFunc(func);
}

void Window::setMainFunc(void (*func)(void))
{
  glutIdleFunc(func);
}

void Window::mainLoop()
{
  glutMainLoop();
}
  
