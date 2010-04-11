#include "intersection.h"

Curve* curve_line_poly(Curve* c, Line* l)
{
  Curve* poly = curve_create(c->n);
  for(int i = 0; i <= c->n; ++i)
  {
    poly->p[i][0] = ((float)i) / ((float)c->n) * 800.0f;
    poly->p[i][1] =
      l->A * c->p[i][0] +
      l->B * c->p[i][1] +
      l->C;
  }
  
  return poly;
}

int curve_line_intersection(Curve* c, Line* l, float **pts)
{
  return curve_bezclip(curve_line_poly(c, l), pts);
}

int curve_line_intersection_quad(Curve* c, Line* l, float **pts)
{
  return curve_quadclip(curve_line_poly(c, l), pts);
}
