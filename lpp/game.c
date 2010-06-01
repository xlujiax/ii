#include "init.h"

#include "bezier.h"
#include "graph.h"
#include "reduction.h"

const float mouse_size = 20;

float* move_mod_x = 0;
float* move_mod_y = 0;

Graph** graphs = 0;
int num_graphs = 0;

void recalc()
{
}

void init()
{
  recalc();
}

void update()
{
}

void draw()
{
  for(int g = 0; g < num_graphs; ++g)
    graph_draw(graphs[g]);

  // mouse
  glColor3f(0.0f, 0.0f, 0.0f);
  glBegin(GL_LINE_STRIP);
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
    //*move_mod_y = getMouseY();

    recalc();
  }
}

void mouse_left_click()
{
  for(int g = 0; g < num_graphs; ++g)
  {
  }
  /*
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
    }*/
}

void mouse_right_click()
{
  move_mod_x = NULL;
  move_mod_y = NULL;
}
