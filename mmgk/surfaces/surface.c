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
  
  s->sOrder = 4;
  s->tOrder = 4;
  
  s->sKnotCount = s->tKnotCount = 8;
  
  s->sKnots = malloc(sizeof(float) * s->sKnotCount);
  s->tKnots = malloc(sizeof(float) * s->sKnotCount);

  s->sKnots[0] = s->tKnots[0] = 0.0;
  s->sKnots[1] = s->tKnots[1] = 0.0;
  s->sKnots[2] = s->tKnots[2] = 0.0;
  s->sKnots[3] = s->tKnots[3] = 0.0;

  s->sKnots[4] = s->tKnots[4] = 1.0;
  s->sKnots[5] = s->tKnots[5] = 1.0;
  s->sKnots[6] = s->tKnots[6] = 1.0;
  s->sKnots[7] = s->tKnots[7] = 1.0;

  s->sStride = 4 * 3;
  s->tStride = 3;

  s->control = malloc(sizeof(float) * 3 * vertical_controls * horizontal_controls);
  
  return s;
}

void surface_render(Surface* s)
{
  gluBeginSurface(s->nurb);

  gluNurbsSurface(s->nurb,
    s->sKnotCount, s->sKnots,
    s->tKnotCount, s->tKnots,
    s->sStride,
    s->tStride,
    s->control,
    s->sOrder, s->tOrder,
    GL_MAP2_VERTEX_3);
  
  //gluBeginTrim(s->nurb);
  //  gluPwlCurve(s->nurb, 8, (GLfloat *)trim, 2, GLU_MAP1_TRIM_2 );
  //gluEndTrim(s->nurb);

  gluEndSurface(s->nurb);

  /*
  glPointSize(5.0);
  glDisable(GL_LIGHTING);
  glColor3f(1.0, 1.0, 0.0);
  glBegin(GL_POINTS);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      glVertex3f(s->control[i][j][0],
        s->control[i][j][1], s->control[i][j][2]);
    }
  }
  glEnd();
  glEnable(GL_LIGHTING);
  */
}

void surface_destroy(Surface* s)
{
  free(s);
}
