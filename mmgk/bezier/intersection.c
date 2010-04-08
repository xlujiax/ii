#include "intersection.h"

void recursive_root_finding(Curve* c, float minu, float maxu, float roots[], int *num_roots)
{
  float midu = (minu + maxu) / 2.0;
  float lenu = maxu - minu;

  Polygon* hull = curve_convex_hull(c);
  float *ints;
  int num_ints = polygon_axis_intersection(hull, &ints);

  //curve_draw(c);
  //polygon_draw_wire(hull);
  
  switch(num_ints)
  {
    case 0:
      polygon_destroy(hull);
      return;
      break;
    case 2:
      if(lenu < 0.001f)
      {
	// dopisz pierwiastek
	roots[(*num_roots)++] = midu;
      }
      else
      {
	// podzial
	Curve* left;
	Curve* right;
	bezier_split(c, 0.5, &left, &right);
	
	recursive_root_finding(left, minu, midu, roots, num_roots);
	curve_destroy(left);
	
	recursive_root_finding(right, midu, maxu, roots, num_roots);
	curve_destroy(right);
      }

      polygon_destroy(hull);
      break;
    default:
      printf("error: bezier_roots, num_ints = %d\n", num_ints);
      for(int i = 0; i < num_ints; ++i)
	printf("%f\n", ints[i]);
      exit(0);
  }
}

// polynomial operations
int bezier_roots(Curve* c, float **roots)
{
  float *temp_roots = malloc((c->n + 1) *sizeof(float));
  int num_roots = 0;

  recursive_root_finding(c, 0, 1, temp_roots, &num_roots);
  
  realloc(temp_roots, num_roots * sizeof(float));
  *roots = temp_roots;
  return num_roots;
}

void bezier_split(Curve* c, float u, Curve** left, Curve** right)
{
  *left = curve_create(c->n);
  *right = curve_create(c->n);

  float (*b)[c->n + 1] = calloc((c->n + 1) * (c->n + 1), sizeof(float));

  for(int i = 0; i <= c->n; ++i)
    b[0][i] = c->p[i][1];

  for(int j = 1; j <= c->n; ++j)
    for(int i = 0; i <= c->n - j; ++i)
      b[j][i] = (1.0f - u) * b[j-1][i] + u * b[j-1][i+1];

  for(int i = 0; i <= c->n; ++i)
  {
    (*left)->p[i][1] = b[i][0];
    (*right)->p[i][1] = b[c->n - i][i];
  }

  float minx = c->p[0][0];
  float maxx = c->p[c->n][0];
  float midx = minx + u * (maxx - minx);

  for(int i = 0; i <= c->n; ++i)
  {
    (*left)->p[i][0] = minx + ((float)i)/((float)c->n)*(midx - minx);
    (*right)->p[i][0] = midx + ((float)i)/((float)c->n)*(maxx - midx);
  }

  free(b);
}

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
  return bezier_roots(curve_line_poly(c, l), pts);
}
