#include "roots.h"

int bezier_quad_roots(Bezier* b, float** roots)
{
  assert(b);
  assert(b->n == 2);

  // quadratic polynomial coefficients in power basis
  float A = b->c[0] - 2*b->c[1] + b->c[2];
  float B = -2*b->c[0] + 2*b->c[1];
  float C = b->c[0];

  float delta = B*B - 4*A*C;

  
  if(delta < 0)
  {
    *roots = 0;
    return 0;
  }
  else
  {
    // quadratic formula and scaling from [0,1] to [a,b]
    float lroot = (-B - sqrtf(delta)) / (2*A) * (b->b - b->a) + b->a;
    float rroot = (-B + sqrtf(delta)) / (2*A) * (b->b - b->a) + b->a;

    if(lroot == rroot)
    {
      *roots = malloc(sizeof(float));
      (*roots)[0] = lroot;
      return 1;
    }
    else
    {
      *roots = malloc(2 * sizeof(float));
      (*roots)[0] = lroot;
      (*roots)[1] = rroot;

      printf("l %f r %f\n", lroot, rroot);
      
      //assert(lroot < rroot);
      return 2;
    }
  }
}
