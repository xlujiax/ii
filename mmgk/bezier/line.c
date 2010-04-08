#include "line.h"

void line_draw(Line* l)
{
  if(fabs(l->A) < 0.001f)
  {
    glBegin(GL_LINES);
    glVertex2f(0, -l->C);
    glVertex2f(1000, -l->C);
    glEnd();
  }
  else
  {
    glBegin(GL_LINES);
    glVertex2f(-l->C / l->A, 0);
    glVertex2f(-(l->C + 1000) / l->A, 1000);
    glEnd();
  }
}

Line* line_create(float a[3], float b[3])
{
  Line* l = malloc(sizeof(Line));
  if(fabs(a[0] - b[0]) < 0.001f)
  {
    l->A = 1;
    l->B = 0;
    l->C = -a[0];
  }
  else
  {
    l->A = (a[1] - b[1]) / (b[0] - a[0]);
    l->B = 1;
    l->C = -l->A * a[0] - a[1];
  }
  
  return l;
}

float line_axis_intersection(Line* l)
{
  return -l->C / l->A;
}

Segment* segment_create(float p[3], float q[3])
{
  Segment* s = malloc(sizeof(Segment));
  memcpy(s->P, p, sizeof(float) * 3);
  memcpy(s->Q, q, sizeof(float) * 3);
  s->ln = line_create(p, q);
  return s;
}

void segment_draw(Segment* s)
{
  glBegin(GL_LINES);
  glVertex3fv(s->P);
  glVertex3fv(s->Q);
  glEnd();
}

int segment_axis_intersection(Segment* s, float* root)
{
  if(s->P[1] * s->Q[1] < 0)
  {
    *root = line_axis_intersection(s->ln);
    return 1;
  }
  else
    return 0;
}
