#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdio.h>
#include <assert.h>

#include "surface.h"
#include "demo.h"

Surface* surf = 0;

void opengl_init(void)
{
  GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 100.0 };

  glClearColor (0.0, 0.0, 0.0, 1.0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_NORMALIZE);
}

float a = 330;
float b = 1;
float c = 0;

void key_press(unsigned char key, int x, int y)
{
  if(key == 'a') c += 0.01;
  if(key == 'd') c -= 0.01;
  if(key == 'w') a += 0.1;
  if(key == 's') a -= 0.1;
}
void opengl_render(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glRotatef(a, b, c, 0.0f);
  glScalef (0.5, 0.5, 0.5);

  assert(surf);
  surface_render(surf);

  glPopMatrix();
  glFlush();

  glutSwapBuffers();

}

void opengl_reshape(GLsizei w, GLsizei h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (45.0, (GLdouble)w/(GLdouble)h, 3.0, 8.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef (0.0, 0.0, -5.0);
}


int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitWindowSize(800, 600);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutCreateWindow("surfaces");

  opengl_reshape(800, 600);
  opengl_init();
  glutIdleFunc(opengl_render);
  glutKeyboardFunc(key_press);
  
  surf = demo();
  
  glutMainLoop();

  surface_destroy(surf);
}
