#include "quadclip.h"

int bezier_quadclip(Bezier* b, float** roots)
{
  if(b->n == 2)
    return bezier_quad_roots(b, roots);
  else
    return 0;
}

void bezier_ox_above(Bezier* b, float** a1, float** a2, float** a3, float** a4)
{
  
}

int bezier_intervals(Bezier* up, Bezier* down, Interval*** intervals)
{
  assert(up->n == 2);
  assert(down->n == 2);

  *intervals = malloc(sizeof(Interval*) * 2);

  (*intervals)[0] = interval_create(0.0f, 0.1f);
  (*intervals)[1] = interval_create(0.4f, 0.7f);

  return 2;
}
