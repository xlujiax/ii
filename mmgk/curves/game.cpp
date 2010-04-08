#include "game.h"
#include "vec.h"
#include "img.h"
#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include "ncs.h"
using namespace std;

#define T(a) cout << #a << " = "<< (a) << endl

float max(float a, float b) { return (a > b) ? a : b; }
float min(float a, float b) { return (a < b) ? a : b; }

float mouse_x = 0;
float mouse_y = 0;

float effective_dist = 20.0f;
float* move_mod_x = 0;
float* move_mod_y = 0;

ncs* splines;
int num_splines;

float (*splines_color)[3];

void selectMessage(int) {}

void init()
{
  glutCreateMenu(selectMessage);
  glutAddMenuEntry("abc", 1);
  glutAddMenuEntry("ABC", 2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

	 
  num_splines = 2;
  splines = (ncs*)malloc(sizeof(ncs) * num_splines);
  splines_color = (float(*)[3])malloc(sizeof(float) * num_splines * 3);

  splines_color[0][0] = 1;
  splines_color[0][1] = 1;
  splines_color[0][2] = 0;

  splines_color[1][0] = 0;
  splines_color[1][1] = 1;
  splines_color[1][2] = 1;

  splines[0].n = 20;
  splines[0].px = (float*)malloc(sizeof(float) * (splines[0].n+1));
  splines[0].py = (float*)malloc(sizeof(float) * (splines[0].n+1));

  {
    float p = 15;
    float q = 30;
    
    float t = -5*3.1415;
    
    for(int i = 0; i <= splines[0].n; ++i)
    {
      t += 31.45 / float(splines[0].n);
      
      splines[0].px[i] = p*t-q*sin(t) + 200;
      splines[0].py[i] = p-q*cos(t) + 100;
    }
  }

  splines[1].n = 20;
  splines[1].px = (float*)malloc(sizeof(float) * (splines[1].n+1));
  splines[1].py = (float*)malloc(sizeof(float) * (splines[1].n+1));

  {
    float r = 0;
    float t = 0;
    
    for(int i = 0; i <= splines[1].n; ++i)
    {
      t += 3.14 / 4;
      r += 5;
      
      splines[1].px[i] = r*cos(t) + 300;
      splines[1].py[i] = r*sin(t) + 300;
    }
  }
    
  for(int i = 0; i < num_splines; ++i)
    splines[i].calc();
}

void key_press(unsigned char key, int x, int y)
{
}

void mouse_click(int button, int state, int x, int y)
{
  if(GLUT_LEFT_BUTTON == button)
  {
    if(GLUT_UP == state)
    {
      move_mod_x = 0;
      move_mod_y = 0;
    }
    else
    {
      for(int s = 0; s < num_splines; ++s)
      for(int i = 0; i <= splines[s].n; ++i)
      {
	float dx = mouse_x - splines[s].px[i];
	float dy = mouse_y - splines[s].py[i];
      
	float dist = sqrt(dx*dx + dy*dy);
      
	if(dist < effective_dist)
	{
	  if(move_mod_x == 0 && move_mod_y == 0)
	  {
	    move_mod_x = &splines[s].px[i];
	    move_mod_y = &splines[s].py[i];
	  }
	  else
	  {
	    float dx_old = mouse_x - *move_mod_x;
	    float dy_old = mouse_y - *move_mod_y;
      
	    float dist_old = sqrt(dx_old*dx_old + dy_old*dy_old);

	    if(dist_old > dist)
	    {
	      move_mod_x = &splines[s].px[i];
	      move_mod_y = &splines[s].py[i];
	    }
	  }
	}
      }
    }
  }
}

void mouse_move(int x, int y)
{
  mouse_x = x;
  mouse_y = y;

  if(move_mod_x != 0 && move_mod_y != 0)
  {
    *move_mod_x = x;
    *move_mod_y = y;
    
    for(int s = 0; s < num_splines; ++s)
      splines[s].calc();
  }
}

void mouse_passive_move(int x, int y)
{
  mouse_move(x,y);
}

void update()
{
}

void draw()
{
  // cursor
  glColor3f(1,1,1);
  glBegin(GL_LINES);
  for(float i = 0; i < 2 * 3.1415; i += 0.1)
    glVertex2f(effective_dist * cosf(i) + mouse_x, effective_dist * sinf(i) + mouse_y);
  glEnd();

  // curve
  for(int s = 0; s < num_splines; ++s)
  {
    glColor3fv(splines_color[s]);

    glBegin(GL_LINE_STRIP);
    for(float arg = 0.0f; arg < 1.0f; arg += 0.001f)
      glVertex2f(splines[s].eval_x(arg), splines[s].eval_y(arg));
    glEnd();
    
    // control points
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <= splines[s].n; i++)
      glVertex2f(splines[s].px[i], splines[s].py[i]);
    glEnd();
  }
}

