#include "quadclip.h"

int bezier_quadclip(Bezier* b, float** roots)
{
  if(b->n == 2)
    return bezier_quad_roots(b, roots);
  else
    return 0;
}

int bezier_above(Bezier* b, Interval*** intervals)
{
  assert(b->n == 2);

  float A = b->c[0] - 2*b->c[1] + b->c[2];
  float B = -2*b->c[0] + 2*b->c[1];

  float* roots = 0;
  int num_roots = bezier_quad_roots(b, &roots);
  
  if(A == 0)
  {
    if(num_roots == 0)
      return 0;
    else
    {
      if(B > 0)
      {
	*intervals = malloc(sizeof(Interval*));
	(*intervals)[0] = interval_create(b->a, roots[0]);
	return 1;
      }
      else
      {
	*intervals = malloc(sizeof(Interval*));
	(*intervals)[0] = interval_create(roots[0], b->b);
	return 1;
      }
    }
  }
  else
  {
    float C = b->c[0];
    float delta = B*B - 4*A*C;

    if(delta == 0)
      return 0;
    else
    {
      if(A > 0)
      {
	if(num_roots == 2)
	{
	  *intervals = malloc(sizeof(Interval*));
	  (*intervals)[0] = interval_create(roots[0], roots[1]);
	  return 1;
	}
	else
	{
	  assert(num_roots == 1);
	  
	  float Wx = -B / (2 * A);
	  if(Wx < roots[0])
	  {
	    *intervals = malloc(sizeof(Interval*));
	    (*intervals)[0] = interval_create(b->a, roots[0]);
	    return 1;
	  }
	  else
	  {
	    *intervals = malloc(sizeof(Interval*));
	    (*intervals)[0] = interval_create(roots[0], b->b);
	    return 1;
	  }
	}
      }
      else
      {
	if(num_roots == 2)
	{
	  *intervals = malloc(sizeof(Interval*) * 2);
	  (*intervals)[0] = interval_create(b->a, roots[0]);
	  (*intervals)[1] = interval_create(roots[1], b->b);
	  return 2;
	}
	else
	{
	  assert(num_roots == 1);
	  
	  float Wx = -B / (2 * A);
	  if(Wx < roots[0])
	  {
	    *intervals = malloc(sizeof(Interval*));
	    (*intervals)[0] = interval_create(roots[0], b->b);
	    return 1;
	  }
	  else
	  {
	    *intervals = malloc(sizeof(Interval*));
	    (*intervals)[0] = interval_create(b->a, roots[0]);
	    return 1;
	  }
	}
      }
    }
  }
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
