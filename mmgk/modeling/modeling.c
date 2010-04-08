#include "modeling.h"

int main_menu;
float mouse_x;
float mouse_y;
int window_width;
int window_height;

int num_cs = 0;
control** cs = 0;

void new_curve(float x, float y)
{
  if(0 == num_cs)
  {
    num_cs = 1;
    cs = malloc(sizeof(control*) * num_cs);

    float (*pts)[2] = malloc(sizeof(float[2]));
    pts[0][0] = x;
    pts[0][1] = y;
    
    cs[0] = control_create(pts, 1);
  }
}

void create()
{
  window_width = 800;
  window_height = 600;
}

void frame()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glColor3f(1,1,1);
  for(int i = 0; i < num_cs; ++i)
  {
    control_draw_line(cs[i]);

    glPointSize(5);
    control_draw_points(cs[i]);
  }

  glutSwapBuffers();
}

void destroy() {}
void shutdown() {}
void mouse_click(int button, int state, int x, int y) {}
void mouse_motion(int x, int y) { mouse_x = x; mouse_y = window_height - y; }
void mouse_passive_motion(int x, int y) { mouse_x = x; mouse_y = window_height - y; }
void open_menu(int id)
{
  switch(id)
  {
    case 1:
      new_curve(mouse_x, mouse_y);
      break;
  }
}

void create_menu()
{
  glutAddMenuEntry("New curve", 1);
}
