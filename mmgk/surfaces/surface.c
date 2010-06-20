#include "surface.h"

void nurbsError(GLenum errorCode)
{
  const GLubyte *estring;

  estring = gluErrorString(errorCode);
  fprintf (stderr, "Nurbs Error: %s\n", estring);
  exit (0);
}

void surface_init_nurb(Surface* s)
{
  s->nurb = gluNewNurbsRenderer();
  gluNurbsProperty(s->nurb, GLU_SAMPLING_TOLERANCE, 25.0);
  gluNurbsProperty(s->nurb, GLU_DISPLAY_MODE, GLU_FILL);
  gluNurbsCallback(s->nurb, GLU_ERROR,
    (GLvoid (*)()) nurbsError);
}

Surface* surface_create_uniform(int vertical_controls, int horizontal_controls)
{
  Surface* s = malloc(sizeof(Surface));
  surface_init_nurb(s);

  s->sControl = vertical_controls;
  s->tControl = horizontal_controls;
  
  s->sOrder = 4;
  s->tOrder = 4;

  assert(s->sControl >= s->sOrder);
  assert(s->tControl >= s->tOrder);
  
  
  s->sKnotCount = s->sControl + s->sOrder;
  s->tKnotCount = s->tControl + s->tOrder;
  
  s->sKnots = malloc(sizeof(float) * s->sKnotCount);
  s->tKnots = malloc(sizeof(float) * s->sKnotCount);

  for(int i = 0; i < s->sOrder - 1; ++i)
    s->sKnots[i] = 0.0;

  for(int i = 0; i < s->tOrder - 1; ++i)
    s->tKnots[i] = 0.0;

  for(int i = s->sOrder - 1; i < s->sKnotCount - s->sOrder + 1; ++i)
  {
    int inner = s->sKnotCount + 1 - 2*s->sOrder;
    int index = i - s->sOrder + 1;
    s->sKnots[i] = ((float)index) / ((float)inner);
  }

  for(int i = s->tOrder - 1; i < s->tKnotCount - s->tOrder + 1; ++i)
  {
    int inner = s->tKnotCount + 1 - 2*s->tOrder;
    int index = i - s->tOrder + 1;
    s->tKnots[i] = ((float)index) / ((float)inner);
  }

  for(int i = s->sKnotCount - s->sOrder + 1; i < s->sKnotCount; ++i)
    s->sKnots[i] = 1;

  for(int i = s->tKnotCount - s->tOrder + 1; i < s->tKnotCount; ++i)
    s->tKnots[i] = 1;

  printf("knotcount %d \n", s->sKnotCount);
  for(int i = 0; i < s->sKnotCount; ++i)
  {
    printf("%f \n", s->sKnots[i]);
  }
  
  s->sStride = s->sControl * 3;
  s->tStride = 3;

  s->control = malloc(sizeof(float) * 3 * s->sControl * s->tControl);
  
  return s;
}

void surface_render(Surface* surf)
{
  gluBeginSurface(surf->nurb);

  gluNurbsSurface(surf->nurb,
    surf->sKnotCount, surf->sKnots,
    surf->tKnotCount, surf->tKnots,
    surf->sStride,
    surf->tStride,
    surf->control,
    surf->sOrder, surf->tOrder,
    GL_MAP2_VERTEX_3);
  
  //gluBeginTrim(s->nurb);
  //  gluPwlCurve(s->nurb, 8, (GLfloat *)trim, 2, GLU_MAP1_TRIM_2 );
  //gluEndTrim(s->nurb);

  gluEndSurface(surf->nurb);

  glPointSize(5.0);
  glDisable(GL_LIGHTING);
  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_POINTS);
  for(int s = 0; s < surf->sControl; s++)
  {
    for(int t = 0; t < surf->tControl; t++)
    {
      glVertex3f(
	surf->control[s*surf->sStride + t*surf->tStride],
	surf->control[s*surf->sStride + t*surf->tStride + 1],
	surf->control[s*surf->sStride + t*surf->tStride + 1]
		 );
    }
  }
  glEnd();
  glEnable(GL_LIGHTING);
}

void surface_destroy(Surface* s)
{
  free(s);
}
