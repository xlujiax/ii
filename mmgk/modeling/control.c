#include "control.h"

control* control_create(float (*pts)[2], int n)
{
  control* c = malloc(sizeof(control));
  c->pts = pts;
  c->n = n;
  return c;
}

void control_destroy(control* c)
{
  free(c);
}

void control_push(control* c, float pt[2])
{
  ++c->n;
  
  c->pts = realloc(c->pts, sizeof(float[2])*c->n);
  memcpy(c->pts[c->n-1], pt, sizeof(float[2]));
}

int control_erase(control* c, float pt[2])
{
  for(int i = 0; i < c->n; ++i)
    if(0 == memcmp(pt, c->pts[i], sizeof(float[2])))
    {
      --c->n;
      memcpy(c->pts[i], c->pts[i+1], sizeof(float[2]) * (c->n - i));
      c->pts = realloc(c->pts, sizeof(float[2])*c->n);
      return 1;
    }
  return 0;
}

void control_write(control* c, FILE* f)
{
  fprintf(f,"[(%d)", c->n);
  for(int i = 0; i < c->n; ++i)
    fprintf(f,"<%f,%f>", c->pts[i][0], c->pts[i][1]);
  fprintf(f,"]\n");
}

control* control_read(FILE* f)
{
  control* c = malloc(sizeof(control));

  if(EOF == fscanf(f, "[(%d)", &c->n))
  {
    free(c);
    return 0;
  }
  c->pts = malloc(sizeof(float[2]) * c->n);

  for(int i = 0; i < c->n; ++i)
    if(EOF == fscanf(f, "<%f,%f>", &c->pts[i][0], &c->pts[i][1]))
    {
      free(c->pts);
      free(c);
      return 0;
    }

  if(EOF == fscanf(f, "]\n"))
  {
    free(c->pts);
    free(c);
    return 0;
  }

  return c;
}

void control_draw_points(control* c)
{
glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, c->pts);
  glDrawArrays(GL_POINTS, 0, c->n);
glDisableClientState(GL_VERTEX_ARRAY);
}

void control_draw_line(control* c)
{
glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, c->pts);
  glDrawArrays(GL_LINE_STRIP, 0, c->n);
glDisableClientState(GL_VERTEX_ARRAY);
}

void control_test()
{
  float (*pts)[2] = malloc(sizeof(float[2]) * 3);
  pts[0][0] = 1;
  pts[0][1] = 1;
  pts[1][0] = 2;
  pts[1][1] = 2;
  pts[2][0] = 3;
  pts[2][1] = 3;
  
  control* c = control_create(pts, 3);
  control_write(c, stdout);

  float pt[2] = {4,4};
  control_push(c, pt);
  control_write(c, stdout);

  float pt2[2] = {3,3};
  control_erase(c, pt2);
  control_write(c, stdout);
}
