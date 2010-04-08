#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include <malloc.h>
using namespace std;

struct nfs
{
  int n;
  float *x;
  float *fx;
  float *h;
  float *M;
  
  nfs() {
    n = 0;
    x = fx = 0;
  }

  void calc();
  float eval(float arg);
};

struct ncs
{
  ncs() {
    n = 0;
    px = px = 0;
  }

  nfs x;
  nfs y;

  int n;
  float* px;
  float* py;

  void calc();
  float eval_x(float arg);
  float eval_y(float arg);
};
