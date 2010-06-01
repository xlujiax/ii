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

void bezier_intervals(Bezier* up, Bezier* down, float** a1, float** a2, float** a3, float** a4)
{
  assert(up->n == 2);
  assert(down->n == 2);

  //float* roots1 = 0;
  //float* roots2 = 0;
  //int num_roots1 = bezier_quad_roots(up, roots1);
  //int num_roots2 = bezier_quad_roots(down, roots2);

  *a1 = malloc(sizeof(float));
  *a2 = malloc(sizeof(float));
  *a3 = malloc(sizeof(float));
  *a4 = malloc(sizeof(float));

  **a1 = 0.1f;
  **a2 = 0.2f;
  **a3 = 0.4f;
  **a4 = 0.5f;
  //assert(0);
}
