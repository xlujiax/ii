#include "quadclip.h"

int bezier_quadclip(Bezier* b, float** roots)
{
  if(b->n == 2)
    return bezier_quad_roots(b, roots);
  else
    return 0;
}
