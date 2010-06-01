#include "samples.h"

Bezier* sample_bezier_sinus(int degree)
{
  Bezier* b = bezier_create(degree);
  for(int i = 0; i <= b->n; ++i)
    b->c[i] = sinf((float)i / (float)b->n);
  return b;
}
