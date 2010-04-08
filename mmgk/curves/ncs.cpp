#include "ncs.h"

void nfs::calc()
{
  if(n == 0 || x == 0 || fx == 0)
    throw "nfs:calc :: arguments not supplied";

  M = (float*)malloc(sizeof(float) * (n+1));
  h = (float*)malloc(sizeof(float) * (n+1));
  
  float* q = (float*)malloc(sizeof(float) * (n+1));
  float* u = (float*)malloc(sizeof(float) * (n+1));
  float* p = (float*)malloc(sizeof(float) * (n+1));
  float* d = (float*)malloc(sizeof(float) * (n+1));
  float* lambda = (float*)malloc(sizeof(float) * (n+1));

  for(int k = 1; k <= n; ++k)
    h[k] = x[k] - x[k-1];

  for(int k = 1; k <= n-1; ++k)
    lambda[k] = h[k] / (h[k] + h[k+1]);

  for(int k = 1; k <= n-1; ++k)
  {
    float f1 = fx[k-1]/((x[k-1] - x[k])*(x[k-1] - x[k+1]));
    float f2 = fx[k]/((x[k] - x[k-1])*(x[k] - x[k+1]));
    float f3 = fx[k+1]/((x[k+1] - x[k-1])*(x[k+1] - x[k]));
    d[k] = 6 * (f1 + f2 + f3);
  }
  q[0] = u[0] = 0;
  for(int k = 1; k <= n - 1; ++k)
  {
    p[k] = lambda[k]*q[k-1]+2;
    q[k] = (lambda[k] - 1)/p[k];
    u[k] = (d[k] - lambda[k]*u[k-1])/p[k];
  }

  M[n-1] = u[n-1];
  for(int k = n - 2; k >= 0; --k)
    M[k] = u[k] + q[k]*M[k+1];

  free(q);
  free(u);
  free(p);
  free(d);
  free(lambda);
}

float nfs::eval(float arg)
{
  int k = 0;
  for(int i = 1; i <= n; ++i)
    if(x[i-1] <= arg && arg <= x[i])
    {
      k = i;
      break;
    }

  return (M[k-1]*(x[k] - arg)*(x[k] - arg)*(x[k] - arg)/6 +
    M[k]*(arg - x[k-1])*(arg - x[k-1])*(arg - x[k-1])/6 +
    (fx[k-1] - M[k-1]*h[k]*h[k]/6)*(x[k] - arg) +
    (fx[k] - M[k]*h[k]*h[k]/6)*(arg - x[k-1]))/h[k];
}

void ncs::calc()
{
  if(n == 0 || px == 0 || py == 0)
    throw "ncs:calc :: arguments not supplied";

  float* dom = (float*)malloc(sizeof(float) * (n+1));
  for(int i = 0; i <= n; ++i)
    dom[i] = ((float)i) / ((float)n);

  x.n = n;
  x.x = dom;
  x.fx = px;
  x.calc();

  y.n = n;
  y.x = dom;
  y.fx = py;
  y.calc();
}

float ncs::eval_x(float arg)
{
  return x.eval(arg);
}
float ncs::eval_y(float arg)
{
  return y.eval(arg);
}
