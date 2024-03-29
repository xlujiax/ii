#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "modeling.h"

int main(int argc, char* argv[])
{
  window_width = window_height = 0;
  
  create();
  
  if(window_width == 0 || window_height == 0)
  {
    printf("create function should set window_width and window_height\n");
    exit(0);
  }

  glutInit(&argc, argv);
  glutInitWindowSize(window_width, window_height);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutCreateWindow("GLUT Window");
  
  glViewport(0, 0, window_width, window_height);
  glMatrixMode(GL_PROJECTION);
  glEnable(GL_DEPTH_TEST);
  glOrtho(0.0f, window_width, 0.0f, window_height, -1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  //glEnable (GL_LINE_SMOOTH);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

  //glEnable (GL_BLEND);
  //glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glutIdleFunc(frame);
  glutMouseFunc(mouse_click);
  glutPassiveMotionFunc(mouse_passive_motion);
  glutMotionFunc(mouse_motion);
  
  glutCreateMenu(open_menu);
  
  create_menu();
  
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  
  glutMainLoop();

  destroy();
  
  return 0;
}
