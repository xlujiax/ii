#include "modeling.h"

int main_menu;
float mouse_x;
float mouse_y;
int window_width;
int window_height;

const float effective_dist = 20;

ncs* active_ncs = 0;
float *active_pt = 0;
int move_pt = 0;

int num_ncs = 0;
ncs** ncss = 0;

void new_cycloide(float x, float y)
{
  int inserter;

  ++num_ncs;
  ncss = realloc(ncss, sizeof(control*) * num_ncs);
  inserter = num_ncs - 1;

  const int vertices = 20;
  float (*pts)[2] = malloc(sizeof(float[2]) * vertices);

  float p = 15;
  float q = 30;
  
  float t = -5*3.1415;
  
  for(int i = 0; i < vertices; ++i)
  {
    t += 31.45 / (float)(vertices);
    
    pts[i][0] = p*t-q*sin(t) + x;
    pts[i][1] = p-q*cos(t) + y;
  }

  ncss[inserter] = ncs_create(control_create(pts, vertices));
  
  active_pt = ncss[inserter]->c->pts[ncss[inserter]->c->n-1];
  active_ncs = ncss[inserter];
}

void new_spiral(float x, float y)
{
  int inserter;

  ++num_ncs;
  ncss = realloc(ncss, sizeof(control*) * num_ncs);
  inserter = num_ncs - 1;

  const int vertices = 20;
  float (*pts)[2] = malloc(sizeof(float[2]) * vertices);
  
  float r = 0;
  float t = 0;
  
  for(int i = 0; i < vertices; ++i)
  {
    t += 3.14 / 4;
    r += 5;
    
    pts[i][0] = r*cos(t) + x;
    pts[i][1] = r*sin(t) + y;
  }
 
  ncss[inserter] = ncs_create(control_create(pts, vertices));
  
  active_pt = ncss[inserter]->c->pts[ncss[inserter]->c->n-1];
  active_ncs = ncss[inserter];
}

void new_curve(float x, float y)
{
  int inserter;

  ++num_ncs;
  ncss = realloc(ncss, sizeof(control*) * num_ncs);
  inserter = num_ncs - 1;
  
  float (*pts)[2] = malloc(sizeof(float[2]));
  pts[0][0] = x;
  pts[0][1] = y;

  ncss[inserter] = ncs_create(control_create(pts, 1));
  
  active_pt = ncss[inserter]->c->pts[ncss[inserter]->c->n-1];
  active_ncs = ncss[inserter];
}

void new_vertex()
{
  if(active_ncs)
  {
    float pt[] = { mouse_x, mouse_y };
    control_push(active_ncs->c, pt);
    ncs_recalc(active_ncs);

    active_pt = active_ncs->c->pts[active_ncs->c->n-1];
  }
}

void erase_ncs()
{
  control_destroy(active_ncs->c);
  
  --num_ncs;
  memcpy(active_ncs, ncss[num_ncs], sizeof(control*));
  
  ncss = realloc(ncss, sizeof(control*) * num_ncs);
  
  active_ncs = 0;
  active_pt = 0;
}

void erase_vertex()
{
  if(active_ncs && active_pt)
  {
    if(active_ncs->c->n == 1)
    {
      erase_ncs();
    }
    else
    {
      control_erase(active_ncs->c, active_pt);
      active_pt = 0;
      ncs_recalc(active_ncs);
    }
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
  for(int i = 0; i < num_ncs; ++i)
  {
    if(active_ncs == ncss[i])
      glColor3f(1,0,0);
    else
      glColor3f(1,1,1);
    
    //control_draw_line(ncss[i]->c);

    const int segments = ncss[i]->c->n - 1;
    if(segments >= 1)
    {
      const float prec = 0.01 / (float)segments;
      
      glBegin(GL_LINE_STRIP);
      for(float t = 0; t <= 1; t += prec)
	glVertex2f(ncs_eval_x(ncss[i], t), ncs_eval_y(ncss[i], t));
      glEnd();
    }
    
    glPointSize(5);
    control_draw_points(ncss[i]->c);
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
  glBegin(GL_LINE_STRIP);
  for(float i = 0; i <= 2.1 * 3.1416; i += 0.1)
    glVertex2f(effective_dist * cosf(i) + mouse_x, effective_dist * sinf(i) + mouse_y);
  glEnd();

  glutSwapBuffers();
}

void mouse_click(int button, int state, int x, int y)
{
  if(GLUT_LEFT_BUTTON == button)
  {
    if(GLUT_DOWN == state)
    {
      active_ncs = 0;
      active_pt = 0;
  
      for(int c = 0; c < num_ncs; ++c)
	for(int i = 0; i < ncss[c]->c->n; ++i)
	{
	  float dx = mouse_x - ncss[c]->c->pts[i][0];
	  float dy = mouse_y - ncss[c]->c->pts[i][1];
      
	  float dist = sqrt(dx*dx + dy*dy);

	  if(dist < effective_dist)
	  {
	    if(active_pt == 0)
	    {
	      active_ncs = ncss[c];
	      active_pt = active_ncs->c->pts[i];
	      move_pt = 1;
	    }
	    else
	    {
	      float dx_old = mouse_x - active_pt[0];
	      float dy_old = mouse_y - active_pt[1];
      
	      float dist_old = sqrt(dx_old*dx_old + dy_old*dy_old);

	      if(dist_old > dist)
	      {
		active_ncs = ncss[c];
		active_pt = active_ncs->c->pts[i];
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
  if(move_pt && active_pt && active_ncs)
  {
    active_pt[0] = mouse_x;
    active_pt[1] = mouse_y;

    if(active_ncs->c->n > 1)
      ncs_recalc(active_ncs);
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
      new_vertex(mouse_x, mouse_y);
      break;
    case 3:
      erase_vertex(active_ncs, active_pt);
      break;
    case 4:
      new_cycloide(mouse_x, mouse_y);
      break;
    case 5:
      new_spiral(mouse_x, mouse_y);
      break;
  }
}

void create_menu()
{
  glutAddMenuEntry("New curve", 1);
  glutAddMenuEntry("New vertex", 2);
  glutAddMenuEntry("Erase vertex", 3);
  glutAddMenuEntry("Cycloide", 4);
  glutAddMenuEntry("Spiral", 5);
}

void destroy() {}
