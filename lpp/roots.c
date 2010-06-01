#include "roots.h"

int bezier_quad_roots(Bezier* b, float** roots)
{
  assert(b);
  assert(b->n == 2);

  int num_roots = 1;
  *roots = malloc(num_roots * sizeof(float));
  (*roots)[0] = 0.5f;

  // quadratic polynomial coefficients in power basis
  //float a = c->;
  //float b = ;
  //float c = ;
  
  return num_roots;
}
