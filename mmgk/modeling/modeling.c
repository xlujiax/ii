#include "modeling.h"

int main_menu;
float mouse_x;
float mouse_y;
int window_width;
int window_height;

const float effective_dist = 20;

control* active_cs = 0;
float *active_pt = 0;
int move_pt = 0;

int num_cs = 0;
control** cs = 0;

void new_curve(float x, float y)
{
  int inserter;
  if(0 == num_cs)
  {
    num_cs = 1;
    cs = malloc(sizeof(control*) * num_cs);
    inserter = 0;
  }
  else
  {
    ++num_cs;
    cs = realloc(cs, sizeof(control*) * num_cs);
    inserter = num_cs - 1;
  }
  
  float (*pts)[2] = malloc(sizeof(float[2]));
  pts[0][0] = x;
  pts[0][1] = y;
  
  cs[inserter] = control_create(pts, 1);
  
  active_pt = pts[0];
  active_cs = cs[inserter];
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
    if(active_cs == cs[i])
      glColor3f(1,0,0);
    else
      glColor3f(1,1,1);
    
    control_draw_line(cs[i]);

    glPointSize(5);
    control_draw_points(cs[i]);
  }

  if(active_pt)
  {
    glColor3f(1,1,0);

    glBegin(GL_POINTS);
    glVertex2fv(active_pt);
    glEnd();
  }
  
  // cursor
  glColor3f(1,1,1);
  glBegin(GL_LINES);
  for(float i = 0; i < 2 * 3.1415; i += 0.1)
    glVertex2f(effective_dist * cosf(i) + mouse_x, effective_dist * sinf(i) + mouse_y);
  glEnd();

  glutSwapBuffers();
}

void destroy() {}
void shutdown() {}
void mouse_click(int button, int state, int x, int y)
{
  if(GLUT_LEFT_BUTTON == button)
  {
    if(GLUT_DOWN == state)
    {
      active_cs = 0;
      active_pt = 0;
  
      for(int c = 0; c < num_cs; ++c)
	for(int i = 0; i <= cs[c]->n; ++i)
	{
	  float dx = mouse_x - cs[c]->pts[i][0];
	  float dy = mouse_y - cs[c]->pts[i][1];
      
	  float dist = sqrt(dx*dx + dy*dy);

	  if(dist < effective_dist)
	  {
	    if(active_pt == 0)
	    {
	      active_cs = cs[c];
	      active_pt = active_cs->pts[i];
	      move_pt = 1;
	    }
	    else
	    {
	      float dx_old = mouse_x - active_pt[0];
	      float dy_old = mouse_y - active_pt[1];
      
	      float dist_old = sqrt(dx_old*dx_old + dy_old*dy_old);

	      if(dist_old > dist)
	      {
		active_cs = cs[c];
		active_pt = active_cs->pts[i];
		move_pt = 1;
	      }
	    }
	  }
	}
    }
    else
      move_pt = 0;
  }
}

void mouse_motion(int x, int y)
{
  mouse_x = x; mouse_y = window_height - y;
  if(move_pt && active_pt)
  {
    active_pt[0] = mouse_x;
    active_pt[1] = mouse_y;
  }
}

void mouse_passive_motion(int x, int y) { mouse_x = x; mouse_y = window_height - y; }
void open_menu(int id)
{
  switch(id)
  {
    case 1:
      new_curve(mouse_x, mouse_y);
      break;
    case 2:
      if(active_cs)
      {
	float pt[] = { mouse_x, mouse_y };
	control_push(active_cs, pt);

	active_pt = active_cs->pts[active_cs->n-1];
      }
      break;
    case 3:
      if(active_cs && active_pt)
      {
	control_erase(active_cs, active_pt);
	active_pt = 0;

	if(active_cs->n == 0)
	{
	  /*
	    usuwanie tej łamanej kontrolnej powoduje segfault

	  control_destroy(active_cs);
	  free(active_cs);
	  */

	  //active_cs = 0;
	}
      }
      break;
  }
}

void create_menu()
{
  glutAddMenuEntry("New curve", 1);
  glutAddMenuEntry("New vertex", 2);
  glutAddMenuEntry("Erase vertex", 3);
}
