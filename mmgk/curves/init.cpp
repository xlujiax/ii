#include <iostream>
using namespace std;

#include <GL/glut.h>

#include "window.h"
#include "game.h"

void loop()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  draw();

  glutSwapBuffers();

  update();
}

void mouse_move_inverse_y(int x, int y)
{
  mouse_move(x, 480 - y);
}
void mouse_passive_move_inverse_y(int x, int y)
{
  mouse_passive_move(x, 480 - y);
}

int main(int argc, char** argv)
{
  try
  {
    Window w(640, 480, argc, argv);
    w.setMainFunc(loop);
    w.setKeyboardFunc(key_press);
    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse_move_inverse_y);
    glutPassiveMotionFunc(mouse_passive_move_inverse_y);
    
    init();
    
    w.mainLoop();
  }
  catch(char const* s)
  {
    cout << "error: " << s << endl;
  }
  return 0;
}
