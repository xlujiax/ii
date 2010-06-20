#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <malloc.h>

typedef struct
{
  GLUnurbsObj *nurb;
  
  int sKnotCount;
  float* sKnots;
    
  int tKnotCount;
  float* tKnots;

  int sStride;
  int tStride; 
  float* control;
  
  int sOrder;
  int tOrder;
  
  GLenum type;
} Surface;

Surface* surface_create_uniform(int vertical_controls, int horizontal_controls);
void surface_render(Surface* s);
void surface_destroy(Surface* s);
