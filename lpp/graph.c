#include "graph.h"

Graph* graph_create(Bezier* b)
{
  Graph* g = malloc(sizeof(Graph));

  g->bezier = b;
  g->draw_control_line = 1;
  g->draw_control_points = 1;
  g->draw_axis = 1;
  g->color_r = 0.0f;
  g->color_g = 0.0f;
  g->color_b = 0.0f;
  g->width = 100.0f;
  g->height = 100.0f;
  g->offset_x = 50.0f;
  g->offset_y = 50.0f;
  g->segments = 50;
  
  return g;
}

void graph_draw(Graph* g)
{
  glColor3f(g->color_r, g->color_g, g->color_b);
  
  if(g->draw_control_line)
  {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= g->bezier->n; i++)
      glVertex2f(
	g->offset_x + g->width * (float)i / (float)g->bezier->n,
	g->offset_y + g->height * g->bezier->c[i]
		 );
    glEnd();
  }

  if(g->draw_control_points)
  {
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <= g->bezier->n; i++)
      glVertex2f(
	g->offset_x + g->width * (float)i / (float)g->bezier->n,
	g->offset_y + g->height * g->bezier->c[i]
		 );
    glEnd();
  }

  if(g->draw_axis)
  {
    glBegin(GL_LINES);
    glVertex2f(g->offset_x, g->offset_y);
    glVertex2f(g->offset_x, g->offset_y + g->height);

    glVertex2f(g->offset_x, g->offset_y);
    glVertex2f(g->offset_x + g->width, g->offset_y);
    glEnd();
  }

  glBegin(GL_LINE_STRIP);
  for(int i = 0; i < g->segments; ++i)
  {
    const float t = (float)i / (float)(g->segments - 1);
    const float ft = bezier_de_casteljau(g->bezier, t);

    glVertex2f(
      g->offset_x + g->width * t,
      g->offset_y + g->height * ft
	       );
  }
  glEnd();
}
