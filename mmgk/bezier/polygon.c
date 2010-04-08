#include "polygon.h"

Polygon* polygon_create(int N)
{
  Polygon* poly = malloc(sizeof(Polygon));
  poly->n = N;
  poly->p = (float(*)[3])malloc(sizeof(float) * poly->n * 3);

  return poly;
}

void polygon_destroy(Polygon* poly)
{
  free(poly->p);
  free(poly);
  poly = 0;
}

void polygon_draw(Polygon* poly)
{
  glBegin(GL_POLYGON);
  for(int i = 0; i < poly->n; ++i)
    glVertex3fv(poly->p[i]);
  glEnd();
}

void polygon_draw_wire(Polygon* poly)
{
  glBegin(GL_LINE_STRIP);
  for(int i = 0; i < poly->n; ++i)
    glVertex3fv(poly->p[i]);
  glVertex3fv(poly->p[0]);
  glEnd();
}

int polygon_axis_intersection(Polygon* poly, float **ret_ints)
{
  int num_ints = 0;
  float *ints = malloc(sizeof(float) * poly->n);

  for(int i = 0; i < poly->n - 1; ++i)
  {
    Segment* s = segment_create(poly->p[i], poly->p[i+1]);
    float root;
    
    if(segment_axis_intersection(s, &root))
      ints[num_ints++] = root;
  }

  // ostatni wierzcholek z pierwszym
  {
    Segment* s = segment_create(poly->p[poly->n - 1], poly->p[0]);
    float root;

    if(segment_axis_intersection(s, &root))
      ints[num_ints++] = root;
  }
  
  ints = realloc(ints, sizeof(float) * num_ints);
  *ret_ints = ints;
  return num_ints;
}
