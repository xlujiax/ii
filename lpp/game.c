#include "init.h"

#include "curve.h"
#include "polygon.h"
#include "line.h"
#include "intersection.h"
#include "hull.h"
#include "utils.h"
#include "reduction.h"

const float mouse_size = 20;

float* move_mod_x = NULL;
float* move_mod_y = NULL;

Curve** curves;
int num_curves;
float (*color_curves)[4];

void init()
{
  glEnable(GL_MAP1_VERTEX_3);
  
  num_curves = 3;
  curves = malloc(sizeof(Curve*) * num_curves);
  color_curves = malloc(sizeof(float) * num_curves * 4);

  int n = 4;

  color_curves[0][0] = 1.0;
  color_curves[0][1] = 1.0;
  color_curves[0][2] = 0.0;
  color_curves[0][3] = 0.5;
  curves[0] = curve_create(n);

  for(int i = 0; i <= n; ++i)
  {
    curves[0]->p[i][0] = i * 30.0f + 300.0f;
    curves[0]->p[i][1] = cosf(i * 30.0f) * 100.0f + 100;
    curves[0]->p[i][2] = 0.0f;
  }

  color_curves[1][0] = 1.0;
  color_curves[1][1] = 0.0;
  color_curves[1][2] = 1.0;
  color_curves[1][3] = 0.5;
  curves[1] = curve_create(n);

  // kopia curves[0]
  for(int i = 0; i <= n; ++i)
  {
    curves[1]->p[i][0] = i * 30.0f + 300.0f;
    curves[1]->p[i][1] = cosf(i * 30.0f) * 100.0f + 100;
    curves[1]->p[i][2] = 0.0f;
  }
  curve_degree_raise(curves[1], 7);

  color_curves[2][0] = 1.0;
  color_curves[2][1] = 1.0;
  color_curves[2][2] = 1.0;
  color_curves[2][3] = 0.5;
  curves[2] = curve_degree_reduction_rec(curves[0], 2);
}

void update()
{
}

void draw()
{
  for(int c = 0; c < num_curves; ++c)
  {
    glColor3fv(color_curves[c]);
    curve_draw(curves[c]);

    curve_draw_control_points(curves[c]);
  }
  // mouse
  glColor3f(1,1,1);
  glBegin(GL_LINES);
  for(float i = 0; i < 2 * 3.1415; i += 0.1)
    glVertex2f(mouse_size * cosf(i) + getMouseX(), mouse_size * sinf(i) + getMouseY());
  glEnd();
}

void key_press(unsigned char key) {}

void mouse_move()
{
  if(move_mod_x != NULL && move_mod_y != NULL)
  {
    //*move_mod_x = getMouseX();
    *move_mod_y = getMouseY();
  }
  
  //curves[1] = curve_degree_reduction(curves[0], curves[1]->n);
}

void mouse_left_click()
{
  for(int c = 0; c < num_curves; ++c)
  {
    for(int i = 0; i <= curves[c]->n; ++i)
    {
      float dx = getMouseX() - curves[c]->p[i][0];
      float dy = getMouseY() - curves[c]->p[i][1];
      
      float dist = dx*dx + dy*dy;
      
      if(dist < mouse_size*mouse_size)
      {
	if(move_mod_x == 0 && move_mod_y == 0)
	{
	  move_mod_x = &curves[c]->p[i][0];
	  move_mod_y = &curves[c]->p[i][1];
	}
	else
	{
	  float dx_old = getMouseX() - *move_mod_x;
	  float dy_old = getMouseY() - *move_mod_y;
	  
	  float dist_old = dx_old*dx_old + dy_old*dy_old;
	  
	  if(dist_old > dist * dist)
	  {
	    move_mod_x = &curves[c]->p[i][0];
	    move_mod_y = &curves[c]->p[i][1];
	  }
	}
      }
    }
  }
}

void mouse_right_click()
{
  move_mod_x = NULL;
  move_mod_y = NULL;
}