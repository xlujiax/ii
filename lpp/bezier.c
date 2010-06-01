#include "bezier.h"

Bezier* bezier_create(int N)
{
  Bezier* b = malloc(sizeof(Bezier));
  b->n = N;
  b->c = (float*)malloc(sizeof(float) * (b->n + 1));

  b->a = 0.0f;
  b->b = 1.0f;

  return b;
}

void bezier_destroy(Bezier* b)
{
  free(b->c);
  free(b);
}

/*
 * It's not the most effective version, as it raises the polynomial one degree (M - b->n) times
 */
void bezier_degree_raise(Bezier* b, int M)
{
  b->c = realloc(b->c, sizeof(float) * (M + 1));
  
  for(int m = b->n + 1; m <= M; ++m, ++b->n)
  {
    b->c[m] = b->c[b->n];
    for(int i = b->n; i >= 1; --i)
      b->c[i] = (i*b->c[i-1]+(m-i)*b->c[i])/((float)m);
  }
}

float bezier_max_coeff_diff(Bezier* b1, Bezier* b2)
{
  // equal degrees are required in opposition to automatically raising degree in order to preserve b1 and b2
  assert(b1->n == b2->n);

  assert(b1->a == b2->a);
  assert(b1->b == b2->b);

  float result = fabs(b1->c[0] - b2->c[0]);
  for(int i = 1; i <= b1->n; ++i)
    if(result < fabs(b1->c[i] - b2->c[i]))
      result = fabs(b1->c[i] - b2->c[i]);
  return result;
}


