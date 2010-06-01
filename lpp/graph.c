#include "graph.h"

Graph* graph_create(Bezier* b)
{
  Graph* g = malloc(sizeof(Graph));

  g->bezier = b;
  g->draw_control_line = 1;
  g->draw_control_points = 1;
  g->color_r = 0.0f;
  g->color_g = 0.0f;
  g->color_b = 0.0f;
  g->width = 100.0f;
  g->height = 100.0f;
  g->offset_x = 50.0f;
  g->offset_y = 50.0f;
  
  return g;
}

void graph_draw(Graph* g)
{
  if(g->draw_control_points)
  {
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <= g->bezier->n; i++)
      glVertex2f((float)i / g->width, g->bezier->c[i]);
    glEnd();
  }
}
